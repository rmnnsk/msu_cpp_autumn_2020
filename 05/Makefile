CC=g++
EX_FLAGS=-std=c++17 -pedantic
O_FLAGS=-std=c++17 -pedantic -c
all: build

build_test1: tests.cpp
	$(CC) $(EX_FLAGS) tests.cpp -o tests

build_test2: tests2.cpp
	$(CC) $(EX_FLAGS) tests2.cpp -o tests2

build: build_test1

test: 
	./tests

test2: build_test2
	
clean:
	rm  *.o
