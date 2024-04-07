CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all: clean
	$(CC) *.c -lcurl -ljson-c -o main && ./main

leaks:
	valgrind --tool=memcheck --leak-check=yes ./main

check:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c

style:
	@clang-format -n -style=google *.c

style_repair:
	@clang-format -i -style=google *.c
	
clean:
	@rm -f main