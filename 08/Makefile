CC=g++
EX_FLAGS=-std=c++17 -pedantic -pthread -g -fsanitize=thread
O_FLAGS=-std=c++17 -pedantic -c
all: build

build_test1: main.cpp
	$(CC) $(EX_FLAGS) main.cpp -o tests

build: build_test1

test: 
	./tests

clean:
	rm  tests
