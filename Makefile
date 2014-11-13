#Author: Mike North
CC=g++

#Author: Mike North
all: interface

#Author: Caleb Rouleau
test: testUtil.o utilities.o
	$(CC) $(CFLAGS) -o testUtil testUtil.o utilities.o -lssl -lcrypto

#Author: Caleb Rouleau
testUtil.o: testUtil.cpp auditlog.h
	$(CC) $(CFLAGS) -c testUtil.cpp

#Author: Mike North
interface: interface.o utilities.o createlog.o add.o closelog.o verifyall.o
	$(CC) $(CFLAGS) -o interface interface.o utilities.o createlog.o add.o closelog.o verifyall.o -lssl -lcrypto

#Author: Caleb Rouleau
interface.o: interface.cpp auditlog.h createlog.h closelog.h verifyall.h
	$(CC) $(CFLAGS) -c interface.cpp

#Author: Caleb Rouleau
createlog.o: createlog.cpp
	$(CC) $(CFLAGS) -c createlog.cpp 
	
#Author: Caleb Rouleau
add.o: add.cpp
	$(CC) $(CFLAGS) -c add.cpp

#Author: Caleb Rouleau
closelog.o: closelog.cpp
	$(CC) $(CFLAGS) -c closelog.cpp

verifyall.o: verifyall.cpp
	$(CC) $(CFLAGS) -c verifyall.cpp

#Author: Caleb Rouleau
utilities.o: utilities.cpp
	$(CC) $(CFLAGS) -c utilities.cpp 
	
#Author: Mike North,Caleb Rouleau
clean:
	rm -f *.o interface testUtil *.log
