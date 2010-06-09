/********************************************
** ARQUIVO DE TESTES PARA FUNÇÕES EXTERNAS  *
********************************************/

#include <stdio.h>
#include "cpu.h"
#include "memory.h"

int main (int argc, char* argv[])
{
	FILE* f;
	char fileName[30];
	
	int numlines = 0;

	printf("in: ");
	scanf("%s", fileName);
	f = fopen(fileName, "r");

	//Load program into memory. MUST REFACTOR
	while(!feof(f))
	{
		fscanf(f, "%d %d", &mem[numlines].inst, &mem[numlines].op);
		printf("i= %d\to= %d\n", mem[numlines].inst, mem[numlines].op);
		numlines++;
	}
	
	//Run program.
	
	return 0;
}

