CC = gcc
CFLAGS = -Wall
LDFLAGS = -lpthread

EXECUTABLES = $(basename $(wildcard *.c))
.PHONY = all clean

all: $(EXECUTABLES)

clean:
	rm -rf $(EXECUTABLES)
