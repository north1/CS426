CC=g++

all: interface

test: testUtil.o utilities.o
	$(CC) $(CFLAGS) -o testUtil testUtil.o utilities.o -lssl -lcrypto

testUtil.o: testUtil.cpp auditlog.h
	$(CC) $(CFLAGS) -c testUtil.cpp

interface: interface.o utilities.o createlog.o add.o closelog.o
	$(CC) $(CFLAGS) -o interface interface.o utilities.o createlog.o add.o closelog.o -lssl -lcrypto

interface.o: interface.cpp auditlog.h createlog.h closelog.h
	$(CC) $(CFLAGS) -c interface.cpp

createlog.o: createlog.cpp
	$(CC) $(CFLAGS) -c createlog.cpp 
	
add.o: add.cpp
	$(CC) $(CFLAGS) -c add.cpp

closelog.o: closelog.cpp
	$(CC) $(CFLAGS) -c closelog.cpp

utilities.o: utilities.cpp
	$(CC) $(CFLAGS) -c utilities.cpp 
	
#-I/usr/local/openssl/include -L/usr/local/openssl/lib main.cpp -lcrypto -ldl


clean:
	rm -f *.o interface testUtil *.log
