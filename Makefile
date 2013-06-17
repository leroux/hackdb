export CC := gcc
export CFLAGS := -Wall -Wextra -Wno-unused-parameter -std=c99 -pedantic -O0 -g

.PHONY: clean all

all: hackdb

hackdb:
	$(CC) $(CFLAGS) hackdb.c -o hackdb

clean:
	rm -f ./hackdb
