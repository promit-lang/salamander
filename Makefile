all: 
	gcc -g -Og -Werror -Wextra -Iinclude/ src/*.c src/salamander/*.c -o ../bin/libsalamander.so