/************
** ENTRADA  *
************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "cpu.h"
#include "memory.h"
#include "globals.h"
#include "memorymanager.h"

unsigned char pc;
unsigned char cs;
unsigned char ds;
char acc;

pthread_t tid0, tid1, tid2;
pthread_mutex_t allocatorMutex = PTHREAD_MUTEX_INITIALIZER;

FILE *tty0, *tty1, *tty2;

void *tty0_thread();
void *tty1_thread();
void *tty2_thread();

process p0, p1, p2;
process running;

int main (int argc, char* argv[])
{
	if(argc != 4)
	{
		printf("Preciso de 3 terminais para continuar. Chame com %s $tty $tty $tty", argv[0]);
		exit(1);
	}
	
	//Open terminals for append
	
	tty0 = fopen(argv[1], "a+");
	tty1 = fopen(argv[2], "a+");
	tty2 = fopen(argv[3], "a+");
	
	if(!tty0)
	{
		printf("Erro ao abrir tty0 (%s). Desistindo.", argv[1]);
		return 1;
	}
	
	if(!tty1)
	{
		printf("Erro ao abrir tty1 (%s). Desistindo.", argv[2]);
		return 1;
	}
	
	if(!tty2)
	{
		printf("Erro ao abrir tty2 (%s). Desistindo.", argv[3]);
		return 1;
	}
	
	//É, multiplos ifs pra testar. Eu sei.
	
	p0 = (process)malloc(sizeof(process));
	p1 = (process)malloc(sizeof(process));
	p2 = (process)malloc(sizeof(process));
	running = (process)malloc(sizeof(process));
	
	
	printf("Criando threads\n");
	
	pthread_create(&tid0, NULL, tty0_thread, NULL);
	pthread_create(&tid1, NULL, tty1_thread, NULL);
	pthread_create(&tid2, NULL, tty2_thread, NULL);

	printf("Threads criadas.\n");

	pthread_join(tid0, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	return 0;
}

void* tty0_thread()
{
	while(1)
	{
		FILE* f;
		char fileName[30];
	
		int numlines = 0;
		int i; //Standard iterator.

		fprintf(tty0, "in: ");
		fscanf(tty0, "%s", fileName);
	
		f = fopen(fileName, "r");

		if(!f)
		{
			printf("Arquivo inválido!");
			exit(-1);
		}
	
		running = p0; // Rodando p0.
		running->tty = tty0;
		
		pthread_mutex_lock(&allocatorMutex);
			if(allocate_block() == OUT_OF_MEMORY)
			{
				printf("SEM MEMÓRIA");
				continue;
			}
		pthread_mutex_unlock(&allocatorMutex);
			
		//Carregar programa na memória.
		while(!feof(f))
		{
			fscanf(f, "%d %d", &mem[numlines + running->cs].inst, &mem[numlines + running->cs].op);
			printf("inst= %d\top= %d\n", mem[numlines + running->cs].inst, mem[numlines + running->cs].op);
			numlines++;
		}
	
		printf("Rodando!\n\n");
	
		for(i = 0; i <= numlines - 1; i++)
		{
			printf("Register dump!\n");
			printf("PC: %d\t CS: %d\t DS: %d\t ACC: %d\n", running->pc, running->cs, running->ds, running->acc);
			
			run_line();
			running->pc++;
		}
		//Terminou execução
		
		pthread_mutex_lock(&allocatorMutex);
			if(free_memory_block(running->block) == UNALLOCATED_MEM)
			{
				printf("Memória já foi desalocada. Algo muito errado aconteceu.");
				continue;
			}
		pthread_mutex_unlock(&allocatorMutex);
		
	}
}

void* tty1_thread()
{
	while(1)
	{
		FILE* f;
		char fileName[30];
	
		int numlines = 0;
		int i; //Standard iterator.

		fprintf(tty1, "in: ");
		fscanf(tty1, "%s", fileName);
	
		f = fopen(fileName, "r");

		if(!f)
		{
			printf("Arquivo inválido!");
			exit(-1);
		}
	
		running = p1; // Rodando p1.
		running->tty = tty1;
	
		pthread_mutex_lock(&allocatorMutex);
			if(allocate_block() == OUT_OF_MEMORY)
			{
				printf("SEM MEMÓRIA");
				continue;
			}
		pthread_mutex_unlock(&allocatorMutex);
			
		//Carregar programa na memória.
		while(!feof(f))
		{
			fscanf(f, "%d %d", &mem[numlines + running->cs].inst, &mem[numlines + running->cs].op);
			printf("inst= %d\top= %d\n", mem[numlines + running->cs].inst, mem[numlines + running->cs].op);
			numlines++;
		}
	
		printf("Rodando!\n\n");
	
		for(i = 0; i <= numlines - 1; i++)
		{
			printf("Register dump!\n");
			printf("PC: %d\t CS: %d\t DS: %d\t ACC: %d\n", running->pc, running->cs, running->ds, running->acc);
			
			run_line();
			running->pc++;
		}
		//Terminou execução
		
		pthread_mutex_lock(&allocatorMutex);
			if(free_memory_block(running->block) == UNALLOCATED_MEM)
			{
				printf("Memória já foi desalocada. Algo muito errado aconteceu.");
				continue;
			}
		pthread_mutex_unlock(&allocatorMutex);
	}
}

void* tty2_thread()
{
	while(1)
	{
		FILE* f;
		char fileName[30];
	
		int numlines = 0;
		int i; //Standard iterator.

		fprintf(tty2, "in: ");
		fscanf(tty2, "%s", fileName);
	
		f = fopen(fileName, "r");

		if(!f)
		{
			printf("Arquivo inválido!");
			exit(-1);
		}
	
		running = p2; // Rodando p2.
		running->tty = tty2;
		
		pthread_mutex_lock(&allocatorMutex);
			if(allocate_block() == OUT_OF_MEMORY)
			{
				printf("SEM MEMÓRIA");
				continue;
			}
		pthread_mutex_unlock(&allocatorMutex);
			
		//Carregar programa na memória.
		while(!feof(f))
		{
			fscanf(f, "%d %d", &mem[numlines + running->cs].inst, &mem[numlines + running->cs].op);
			printf("inst= %d\top= %d\n", mem[numlines + running->cs].inst, mem[numlines + running->cs].op);
			numlines++;
		}
	
		printf("Rodando!\n\n");
	
		for(i = 0; i <= numlines - 1; i++)
		{
			printf("Register dump!\n");
			printf("PC: %d\t CS: %d\t DS: %d\t ACC: %d\n", running->pc, running->cs, running->ds, running->acc);
			
			run_line();
			running->pc++;
		}
		//Terminou execução
		
		pthread_mutex_lock(&allocatorMutex);
			if(free_memory_block(running->block) == UNALLOCATED_MEM)
			{
				printf("Memória já foi desalocada. Algo muito errado aconteceu.");
				continue;
			}
		pthread_mutex_unlock(&allocatorMutex);
	}
}