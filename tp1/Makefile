CC=g++
CFLAGS=-I. -Wall -Wextra -Werror -std=c++11 -pedantic -O2 -g
DEPS = campanha.hpp
OBJ = campanha.o main.o 

all: main

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o tp01 $^ $(CFLAGS)

run: 
	./tp01 < input.txt

clean:
	rm -f *.o tp01