CC = gcc
CFLAGS = -g -c -Wall -lpthread

all: main.o cpu.o memorymanager.o
	$(CC) main.o cpu.o memorymanager.o -o vm

main.o: main.c cpu.h memory.h globals.h
	$(CC) $(CFLAGS) main.c

cpu.o: cpu.c cpu.h defines.h globals.h memory.h
	$(CC) $(CFLAGS) cpu.c
	
memorymanager.o: memorymanager.c memorymanager.h memory.h globals.h defines.h
	$(CC) $(CFLAGS) memorymanager.c
	
clean:
	rm -rf *.o vm
