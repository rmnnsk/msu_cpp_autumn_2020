CC=g++
EX_FLAGS=-std=c++17 -pedantic
O_FLAGS=-std=c++17 -pedantic -c
all: build

build_test1: tests.cpp
	$(CC) $(EX_FLAGS) tests.cpp -o tests

build: build_test1

test: 
	./tests

clean:
	rm  *.o
