CC=g++

all: interface

interface: interface.o
	$(CC) $(CFLAGS) -o interface interface.o -lssl -lcrypto

interface.o: interface.cpp auditlog.h
	$(CC) $(CFLAGS) -c interface.cpp

utilities.o: utilities.cpp auditlog.h
	$(CC) $(CFLAGS) -c utilities.cpp

clean:
	rm -f *.o interface
