CC      := gcc
CFLAGS  := -std=gnu99 -Wall -pthread
LDFLAGS :=
OBJS    := async.o async_test.o

all: async_test

async_test: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CLAGS) -c $^

clean:
	rm -rf $(OBJS) async_test
