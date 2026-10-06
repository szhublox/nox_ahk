CC = gcc
CFLAGS = $(shell pkg-config --libs xi xtst x11)

default: conjurer wizard

conjurer: main.c conjurer.c
	$(CC) $(CFLAGS) conjurer.c -o conjurer
wizard: main.c wizard.c
	$(CC) $(CFLAGS) wizard.c -o wizard
