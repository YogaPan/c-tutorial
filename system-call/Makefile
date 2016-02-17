CC = gcc
CFLAGS = -Wall
LDFLAGS = -pthread

EXECUTABLES = $(basename $(wildcard *.c))
.PHONY = all clean

all: $(EXECUTABLES)

clean:
	rm -rf $(EXECUTABLES)
