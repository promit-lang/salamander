all: 
	gcc -g -Og -Wall -Wextra -Iinclude/ src/*.c src/salamander/*.c -shared -o ../bin/libsalamander.so