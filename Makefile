# Don't forget to put library path to $LD_LIBRARY_PATH variable
# LD_LIBRARY_PATH=/home/greybaca/base_alt_work_directory/lib:$LD_LIBRARY_PATH
# export LD_LIBRARY_PATH

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

# ONLY FOR DEBUG
#CFLAGS = -std=c11

all: build
	@bin/main

build: cr_lib
	@$(CC) $(CFLAGS) main.c cli_data/*.c -lcurl -ljson-c -lbasealt -L lib -o bin/main

cr_objects: clean
	@$(CC) $(CFLAGS) -c -fpic ./functions/*.c -lcurl -ljson-c
	@mv *.o ./out

cr_lib: clean cr_objects
	@$(CC) $(CFLAGS) ./out/*.o -shared -Wl,-soname,libbasealt.so.1 -lcurl -ljson-c -o ./lib/libbasealt.so.1.1.1
	@ln -s libbasealt.so.1.1.1 ./lib/libbasealt.so.1
	@ln -s libbasealt.so.1 ./lib/libbasealt.so

run: clean
	$(CC) $(CFLAGS) *.c ./functions/*.c -lcurl -ljson-c -o ./bin/main && ./bin/main
	
leaks:
	valgrind --tool=memcheck --leak-check=yes ./bin/main

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c functions/*.c cli_data/*.c

style:
	clang-format -n -style=google *.c

style_repair:
	clang-format -i -style=google *.c
	
clean:
	@rm -f ./bin/main ./out/*.o ./lib/*
	