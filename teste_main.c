/********************************************
** ARQUIVO DE TESTES PARA FUNÇÕES EXTERNAS  *
********************************************/

#include <stdio.h>
#include "cpu.h"

int main (int argc, char* argv[])
{
	FILE* f;
	char x, y;
	char nomeArq[30];

	printf("in: ");
	scanf("%s", nomeArq);
	f = fopen(nomeArq, "r");
	
	while(!feof(f))
	{
		fscanf(f, "%d %d", &x, &y);
		printf("x= %d\ty= %d\n", x, y);
	}
	return 0;
}

