CC     = gcc
CFLAGS = -Wall -std=gnu99 -DRANDOM_FILE='"./random.txt"' -DARRAY_SIZE=10000
OBJS   = $(subst %.c,%.o,$(wildcard *.c))
EXEC   = test_time

.PHONY: all random clean plot

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^

tags:
	ctags -R *

random: ./scripts/generate.py
	python3 ./scripts/generate.py

plot:
	python3 ./scripts/plot.py

clean:
	rm -rf $(EXECUTABLES) random.txt
