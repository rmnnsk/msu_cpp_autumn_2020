CC=g++
EX_FLAGS=-std=c++17 -Wall -pedantic
O_FLAGS=-std=c++17 -Wall -pedantic -c
all: build

build_matrix: Matrix.cpp
	$(CC) $(O_FLAGS) Matrix.cpp -o Matrix.o

build_test: tests.cpp
	$(CC) $(O_FLAGS) tests.cpp -o tests.o

build: build_matrix build_test
	$(CC) $(EX_FLAGS) Matrix.o tests.o -o tests

test: 
	./tests

clean:
	rm  *.o
