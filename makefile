CC = gcc
CFLAGS = -c -Wall -lpthread

all: main.o cpu.o
	$(CC) main.o cpu.o -o vm

main.o: main.c cpu.h memory.h globals.h
	$(CC) $(CFLAGS) main.c

cpu.o: cpu.c cpu.h defines.h globals.h memory.h
	$(CC) $(CFLAGS) cpu.c
	
clean:
	rm -rf *.o vm
