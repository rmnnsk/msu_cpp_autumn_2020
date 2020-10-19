CC=g++
EX_FLAGS=-std=c++17 -Wall -pedantic
O_FLAGS=-std=c++17 -Wall -pedantic -c
all: build

build_parser: parser.cpp
	$(CC) $(O_FLAGS) parser.cpp -o parser.o

build_test: tests.cpp
	$(CC) $(O_FLAGS) tests.cpp -o tests.o

build: build_parser build_test
	$(CC) $(EX_FLAGS) parser.o tests.o -o tests

test: 
	./tests

clean:
	rm  *.o