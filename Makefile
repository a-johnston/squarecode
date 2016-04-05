build: src/code.h src/code.c
	gcc -O3 -Wall -Werror -Wextra -Wpedantic src/code.c -o bin/code
