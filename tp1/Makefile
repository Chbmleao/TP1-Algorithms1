CC=g++
CFLAGS=-I. -Wall -Wextra -Werror -std=c99 -pedantic -O2
DEPS = campanha.h
OBJ = campanha.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: 
	./main

clean:
	rm -f *.o main