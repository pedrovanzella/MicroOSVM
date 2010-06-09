CC = gcc
CFLAGS = -c -Wall
BUILDDIR = build/

all: teste_main.o cpu.o
	$(CC) $(BUILDDIR)main.o $(BUILDDIR)cpu.o -o $(BUILDDIR)main

main.o: main.c cpu.h memory.h
	$(CC) $(CFLAGS) $(BUILDDIR)main.c

cpu.o: cpu.c cpu.h defines.h globals.h memory.h
	$(CC) $(CFLAGS) $(BUILDDIR)cpu.c
	
clean:
	rm -rf $(BUILDDIR)*.o $(BUILDDIR)main
