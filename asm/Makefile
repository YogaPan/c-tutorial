CC = gcc
CFLAGS = -Wall

all: hello

hello: hello.o
	ld hello.o -o hello

hello.o: hello.S
	gcc -c hello.S

clean:
	rm -rf hello hello.o
