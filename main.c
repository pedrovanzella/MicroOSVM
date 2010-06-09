/********************************************
** ARQUIVO DE TESTES PARA FUNÇÕES EXTERNAS  *
********************************************/

#include <stdio.h>
#include "cpu.h"
#include "memory.h"
#include "globals.h"

unsigned char pc;
unsigned char cs;
unsigned char ds;
char acc;

int main (int argc, char* argv[])
{
	FILE* f;
	char fileName[30];
	
	int numlines = 0;
	int i; //Standard iterator.

	printf("in: ");
	scanf("%s", fileName);
	
	f = fopen(fileName, "r");

	if(!f)
	{
		printf("Invalid file!");
		return -1;
	}
	//Load program into memory. MUST REFACTOR
	while(!feof(f))
	{
		fscanf(f, "%d %d", &mem[numlines].inst, &mem[numlines].op);
		printf("i= %d\to= %d\n", mem[numlines].inst, mem[numlines].op);
		numlines++;
	}
	
	printf("Will now run.\n\n");
	
	//Run program.
	pc = 0;
	cs = 0;
	ds = 128;
	for(i = 0; i <= numlines - 1; i++)
	{
		printf("Register dump!\n");
		printf("PC: %d\t CS: %d\t DS: %d\t ACC: %d\n", pc, cs, ds, acc);
		printf("line %d: ", i);
		run_line();
		pc++;
		printf("\n");
	}
	
	return 0;
}

