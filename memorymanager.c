/**************************
** GERENCIADOR DE MEMÓRIA *
**************************/

#include <stdio.h>
#include "memorymanager.h"
#include "memory.h"
#include "globals.h"
#include "defines.h"

process running; /* Ponteiro para o processo rodando */
char allocated_blocks[4]; /* Vetor que diz quais blocos estão alocados */

int allocate_block()
{
	int i;
	
	for(i = 0; i <= 3; i++)
	{
		if(!allocated_blocks[i]) //Se o bloco não estiver alocado
		{
			printf("Alocando bloco %d para processo.", i);
			allocated_blocks[i] = 1;
			running->block = i;
			if(i == 0) running->cs = 0; //Primeiro bloco deve começar em 0, não -1.
			else running->cs = (i * 32) - 1; // Código do programa começa em 0, 31, 63 ou 95
			running->ds = (i * 32) + 128; // Dados do programa começam em 128, 160, 192 ou 224
			
			return i;
		}
	}
	return OUT_OF_MEMORY; // Se não há memória.
}

int free_memory_block(int block)
{
	if(!allocated_blocks[block]) return UNALLOCATED_MEM;
	allocated_blocks[block] = 0;
	return 0;
}