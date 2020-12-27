CC := gcc
CFLAGS := -g -std=c99 -Wall -Wextra -Isrc
FILES := src/cuckoo_hash.c src/main.c
OBJECTS := $(FILES:.c=.o)

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o cuckoo

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm src/*.o
	rm cuckoo

.PHONY: all clean
