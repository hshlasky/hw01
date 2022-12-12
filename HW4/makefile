CC=gcc
CCLINK=$(CC)
CFLAGS=-c -g -Wall -std=c99
OBJS=grades.o
EXEC=prog.exe
RM=rm -rf *.o *.so

# The first rule is invoked by default
libgrades.so: grades.o
	$(CC) -shared grades.o -o libgrades.so -llinked-list -L.

grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -fpic grades.c

clean:
	$(RM)

