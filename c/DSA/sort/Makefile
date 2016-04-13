CC = gcc
CFLAGS = -Wall -std=gnu99 -DRANDOM_FILE='"./random.txt"' -DARRAY_SIZE=50000
EXECUTABLES = $(basename $(wildcard *.c))

.PHONY: all random clean

all: $(EXECUTABLES)

tags:
	ctags -R *

random: ./scripts/generate.py
	python3 ./scripts/generate.py

plot:


clean:
	rm -rf $(EXECUTABLES) random.txt
