CC      = gcc
CFLAGS  = -Wall -std=gnu99
LDFLAGS = -pthread
OBJS    = $(patsubst %.o,%.c,$(wildcard *.c))

all: requests

requests: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

tags:
	ctags -R *

clean:
	rm -rf $(OBJS)
