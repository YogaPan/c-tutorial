CC := gcc
CFLAGS := -Wall -std=gnu99 -O2
LDFLAGS :=
EXEC := tcp

all: $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $^ -o $@ $(CFLAGS)

clean:
	rm -rf $(EXEC)
