CC=g++
EX_FLAGS=-std=c++17 -Wall -pedantic
O_FLAGS=-std=c++17 -Wall -pedantic -c
all: build

build_parser: parser.cpp
	$(CC) $(O_FLAGS) parser.cpp -o parser.o

build_test: test.cpp
	$(CC) $(O_FLAGS) test.cpp -o test.o

build: build_parser build_test
	$(CC) $(EX_FLAGS) parser.o test.o -o test

test: 
	./test

clean:
	rm  *.o