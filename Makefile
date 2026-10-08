CC = gcc
CFLAGS = $(shell pkg-config --libs xi xtst x11)

default: conjurer wizard

main.o: main.c
	$(CC) $(CFLAGS) -c $?
conjurer: main.o conjurer.c
	$(CC) $(CFLAGS) $? -o conjurer
wizard: main.o wizard.c
	$(CC) $(CFLAGS) $? -o wizard

.PHONY: clean
clean:
	rm -f main.o conjurer wizard
