
all:
	gcc -std=c99 -I. -Wall main.c cuckoo_hash.c -o cuckoo
