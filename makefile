CC = gcc
CFLAGS = -Wall -ansi -O3

amazeme: main.c 
	$(CC) $(CFLAGS) -o amazeme main.c amazefunc.c
