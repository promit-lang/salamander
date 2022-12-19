/** Implements the API function of 'salamander/object.h'. */

// In case you are wondering, 'object.h' has already been included by the 
// 'salamander_value.h'.

#include <salamander_value.h>

ObjFn* salamander_ObjFn_new(SalamanderVM* vm) {
    FnDebug* debug = ALLOCATE(FnDebug, 1u);
    ObjFn* fn = ALLOCATE(ObjFn, 1u);

    fn -> debug = debug;

    salamander_IntBuffer_init(&debug -> lines);
    salamander_ByteBuffer_init(&fn -> code);
    salamander_ValueBuffer_init(&fn -> pool);

    return fn;
}

void salamander_ObjFn_free(SalamanderVM* vm, ObjFn* fn) {
    salamander_ByteBuffer_free(vm, &fn -> code);
    salamander_IntBuffer_free(vm, &fn -> debug -> lines);
    salamander_ValueBuffer_free(vm, &fn -> pool);

    FREE(FnDebug, fn -> debug);
    FREE(ObjFn, fn);
}