CC = gcc
CFLAGS = $(shell pkg-config --libs xi xtst x11)

default: wizard

wizard: wizard.c
	$(CC) $(CFLAGS) $? -o wizard
