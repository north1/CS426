CC=gcc

all: interface

interface: interface.o
	$(CC) $(CFLAGS) -o interface interface.o

interface.o: interface.c
	$(CC) $(CFLAGS) -c interface.c

clean:
	rm -f *.o interface
