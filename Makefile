CC=g++

all: interface

test: testUtil.o utilities.o
	$(CC) $(CFLAGS) -o testUtil testUtil.o utilities.o -lssl -lcrypto

testUtil.o: testUtil.cpp auditlog.h
	$(CC) $(CFLAGS) -c testUtil.cpp

interface: interface.o utilities.o createlog.o
	$(CC) $(CFLAGS) -o interface interface.o utilities.o createlog.o -lssl -lcrypto

interface.o: interface.cpp auditlog.h createlog.h
	$(CC) $(CFLAGS) -c interface.cpp

createlog.o: createlog.cpp
	$(CC) $(CFLAGS) -c createlog.cpp 
	
utilities.o: utilities.cpp
	$(CC) $(CFLAGS) -c utilities.cpp 
	
#-I/usr/local/openssl/include -L/usr/local/openssl/lib main.cpp -lcrypto -ldl


clean:
	rm -f *.o interface testUtil
