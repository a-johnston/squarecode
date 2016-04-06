build: src/code.h src/code.c src/testbench.c
	gcc -O3 -Wall -Werror -Wextra -Wpedantic src/testbench.c -o bin/testbench
