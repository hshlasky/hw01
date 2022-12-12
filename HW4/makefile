CC=gcc
CCLINK=$(CC)
CFLAGS=-c -g -Wall -std=c99
OBJS=grades.o
EXEC=libgrades.so
RM=rm -rf *.o libgrades.so

# The first rule is invoked by default
$(EXEC): $(OBJS)
	$(CC) -shared $(OBJS) -o libgrades.so -llinked-list -L.

grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -fpic grades.c

clean:
	$(RM)

