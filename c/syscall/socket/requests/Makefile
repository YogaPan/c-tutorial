CC      = gcc
CFLAGS  = -Wall
LDFLAGS = -pthread
OBJS    = $(patsubst %.o,%.c,$(wildcard *.c))

all: get

get: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

tags:
	ctags -R *
