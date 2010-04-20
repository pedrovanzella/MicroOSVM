/********************************************
** ARQUIVO DE TESTES PARA FUNÇÕES EXTERNAS  *
********************************************/

#include <stdio.h>

int main (int argc, char* argv[])
{
	FILE* f;
	char x, y;
	char nomeArq[30];

	printf("in: \n");
	scanf("%s", nomeArq);
	f = fopen(nomeArq, "r");
	
	while(!feof(f))
	{
		fscanf(f, "%d %d", &x, &y);
		printf("\nx= %d\ty= %d", x, y);
	}
}

