CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: build 

build: allocator.cpp 
	$(CC) $(FLAGS) allocator.cpp -o alloc

test: 
	valgrind ./alloc

clean:
	rm -f alloc
