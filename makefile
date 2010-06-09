CC = gcc
CFLAGS = -c -Wall

all: teste_main.o cpu.o
	$(CC) teste_main.o cpu.o -o main

teste_main.o: teste_main.c cpu.h
	$(CC) $(CFLAGS) teste_main.c

cpu.o: cpu.c cpu.h defines.h globals.h memory.h
	$(CC) $(CFLAGS) cpu.c
	
clean:
	rm -rf ./*.o main
