#include <salamander_vm.h>

// Helper for inheritant object allocator.

#define ALLOCATE_OBJ(type, obj_type)                                      \
    (type*) allocate_object(vm, sizeof(type), obj_type);

DEFINE_BUFFER(Value, Value);

static Obj* allocate_object(SalamanderVM* vm, size_t size, ObjType type) {
    Obj* object = (Obj*) salamander_Memory_reallocate(vm, NULL, 0u, size);

    object -> type = type;
    object -> next = vm -> last;

    // Adding to the object linked list in order to track all the allocated 
    // objects and free it when the VM frees or the GC collects.

    vm -> last = object;

    return object;
}

// ObjFn* salamander_ObjFn_new(SalamanderVM*);
// 
// Creates and returns a new 'ObjFn' object.
// 
// Note: The objects are freed by the VM and the GC. So, there is no 
//       respective '_free' function for objects.

ObjFn* salamander_ObjFn_new(SalamanderVM* vm) {
    ObjFn* fn = ALLOCATE_OBJ(ObjFn, OBJ_FN);

    // The 'FnDebug' struct to keep the debugging info such as line numbers 
    // etc.

    FnDebug* debug = ALLOCATE(FnDebug);

    // Initialize the line buffer.

    salamander_IntBuffer_init(&debug -> lines);

    // Initialize the function debugging info.

    fn -> debug = debug;

    // Initialize the byte buffer to store instructions.

    salamander_ByteBuffer_init(&fn -> code);

    // Initialize the constant pool.

    salamander_ValueBuffer_init(&fn -> pool);

    return fn;
}

// int salamander_fn_get_line_of_byte(ObjFn*, int);
//
// Gets the source line number where the provided byte is compiled from.

int salamander_ObjFn_byte_line(ObjFn* fn, int offset) {
    IntBuffer buffer = fn -> debug -> lines;

    // Use binary search like approach to find the line number.

    int left = 0, right = buffer.count - 1, mid = (left + right) / 2;

    while(left != right) {
        if(likely(offset <= buffer.data[mid])) {
            if(likely(mid == 0 || offset > buffer.data[mid - 1])) 
                return mid + 1;
            else right = mid - 1;
        } else left = mid + 1;

        mid = (right + left) / 2;
    }

    // Above loop doesn't cover the very last line, thus checking whether it
    // is the last line which should be returned.

    if(likely(mid == right && offset <= buffer.data[mid])) 
        return mid + 1;

    // Will not reach, cause it should be ensured by the compiler that a valid
    // line number exists of provided byte offset.

    UNREACHABLE();

    return -1;
}

// void salamander_ObjFn_write_byte(SalamanderVM*, ObjFn*, uint8_t, int);
//
// Appends provided byte to the bytecode sequence with encoding the line 
// number the byte is compiled from.

void salamander_ObjFn_write_byte(SalamanderVM* vm, 
    ObjFn* fn, uint8_t byte, int line) 
{
    // Add the line number as debugging info.

    if(unlikely(line > fn -> debug -> lines.count)) 
        salamander_IntBuffer_write(vm, &fn -> debug -> lines, fn -> code.count);
    else fn -> debug -> lines.data[line - 1]++;    // Run-length encoding.

    // Insert the byte into the buffer.

    salamander_ByteBuffer_write(vm, &fn -> code, byte);
}

// void salamander_ObjFn_write_short(SalamanderVM*, ObjFn*, uint16_t, int);
// 
// Appends provided short (unsigned 16-bit integer) to the bytecode sequence
// by disecting it to bytes.

void salamander_ObjFn_write_short(SalamanderVM* vm, ObjFn* fn, 
    uint16_t bytes, int line) 
{
    salamander_ObjFn_write_byte(vm, fn, (uint8_t) ((bytes >> 0x8) & 0xFF), line);
    salamander_ObjFn_write_byte(vm, fn, (uint8_t) (bytes & 0xFF), line);
}

// int salamander_ObjFn_write_constant(SalamanderVM*, ObjFn*, Value);
//
// Writes the provided constant to the constant pool.

int salamander_ObjFn_write_constant(SalamanderVM* vm, ObjFn* fn, Value constant) {
    int idx = fn -> pool.count;

    salamander_ValueBuffer_write(vm, &fn -> pool, constant);

    return idx;
}