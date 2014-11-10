CC=g++

all: interface

interface: interface.o
	$(CC) $(CFLAGS) -o interface interface.o

interface.o: interface.cpp
	$(CC) $(CFLAGS) -c interface.cpp

clean:
	rm -f *.o interface
