CC = gcc
CFLAGS = -c -Wall
BUILDDIR = build/

all: teste_main.o cpu.o
	$(CC) $(BUILDDIR)teste_main.o $(BUILDDIR)cpu.o -o $(BUILDDIR)main

teste_main.o: teste_main.c cpu.h
	$(CC) $(CFLAGS) $(BUILDDIR)teste_main.c

cpu.o: cpu.c cpu.h defines.h globals.h memory.h
	$(CC) $(CFLAGS) $(BUILDDIR)cpu.c
	
clean:
	rm -rf $(BUILDDIR)*.o $(BUILDDIR)main
