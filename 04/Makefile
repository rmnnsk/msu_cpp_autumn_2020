CC=g++
EX_FLAGS=-std=c++17 -pedantic
O_FLAGS=-std=c++17 -pedantic -c
all: build

build_bigint: BigInt.cpp
	$(CC) $(O_FLAGS) BigInt.cpp -o BigInt.o

build_test: tests.cpp
	$(CC) $(O_FLAGS) tests.cpp -o tests.o

build: build_bigint build_test
	$(CC) $(EX_FLAGS) BigInt.o tests.o -o tests

test: 
	./tests

clean:
	rm  *.o
