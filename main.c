/************
** ENTRADA  *
************/

/* TODO: thread escalonadora conta até x, trava duas threads, destrava uma, repete ad infinitum. Usar três mutexes. */


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

pthread_t tid0, tid1, tid2, tesc;
pthread_mutex_t allocatorMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t runningMutex = PTHREAD_MUTEX_INITIALIZER;

FILE *tty0, *tty1, *tty2;

void *tty0_thread();
void *tty1_thread();
void *tty2_thread();

void *escalonador();

process p0, p1, p2;
process running;

int main (int argc, char* argv[])
{
	if(argc != 4)
	{
		printf("Preciso de 3 terminais para continuar. Chame com %s $tty $tty $tty\n", argv[0]);
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
	running = p0; //Arbitrariamente o primeiro programa é p0.
	
	p0->acc = 0;
	p0->pc  = 0;
	p0->ds  = 0;
	p0->cs  = 0;
	
	p1->acc = 0;
	p1->pc  = 0;
	p1->ds  = 0;
	p1->cs  = 0;
	
	p2->acc = 0;
	p2->pc  = 0;
	p2->ds  = 0;
	p2->cs  = 0;
	
	
	
	
	printf("Criando threads\n");
	
	pthread_create(&tesc, NULL, escalonador, NULL);
	pthread_create(&tid0, NULL, tty0_thread, NULL);
	pthread_create(&tid1, NULL, tty1_thread, NULL);
	pthread_create(&tid2, NULL, tty2_thread, NULL);

	printf("Threads criadas.\n");

	pthread_join(tid0, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tesc, NULL);
	
	return 0;
}

void* escalonador()
{
	while(1)
	{
		pthread_mutex_lock(&runningMutex);
			if(running == p0)
			{
				if(p1->ready) running = p1;
				else if(p2->ready) running = p2;
			}
			if(running == p1)
			{
				if(p2->ready) running = p2;
				else if(p0->ready) running = p0;
			}
			if(running == p2)
			{
				if(p0->ready) running = p0;
				else if(p1->ready) running = p1;
			}
		pthread_mutex_unlock(&runningMutex);
	}
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
			printf("Arquivo inválido!\n");
			exit(-1);
		}
	
		p0->tty = tty0;
		p0->ready = 0;
		
		pthread_mutex_lock(&allocatorMutex);
			if(allocate_block() == OUT_OF_MEMORY)
			{
				printf("SEM MEMÓRIA\n");
				continue;
			}
		pthread_mutex_unlock(&allocatorMutex);
			
		//Carregar programa na memória.
		while(!feof(f))
		{
			fscanf(f, "%d %d", &mem[numlines + p0->cs].inst, &mem[numlines + p0->cs].op);
			printf("inst= %d\t\top= %d\n", mem[numlines + p0->cs].inst, mem[numlines + p0->cs].op);
			numlines++;
		}
		
		p0->ready = 1;
		printf("Rodando!\n\n");
	
		while(1)
		{
			//MUTEX
			pthread_mutex_lock(&runningMutex);
				if(running == p0)
				{
					printf("PC: %d\t CS: %d\t DS: %d\t ACC: %d\n", running->pc, running->cs, running->ds, running->acc);
					if(run_line() == PROG_END) break;
					running->pc++;
				}
			pthread_mutex_unlock(&runningMutex);
			//MUTEX END
		}
		//Terminou execução
		
		pthread_mutex_lock(&allocatorMutex);
			if(free_memory_block(running->block) == UNALLOCATED_MEM)
			{
				printf("Memória já foi desalocada. Algo muito errado aconteceu.\n");
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
			printf("Arquivo inválido!\n");
			exit(-1);
		}
		
		p1->tty = tty1;
		p1->ready = 0;
	
		pthread_mutex_lock(&allocatorMutex);
			if(allocate_block() == OUT_OF_MEMORY)
			{
				printf("SEM MEMÓRIA\n");
				continue;
			}
		pthread_mutex_unlock(&allocatorMutex);
			
		//Carregar programa na memória.
		while(!feof(f))
		{
			fscanf(f, "%d %d", &mem[numlines + p1->cs].inst, &mem[numlines + p1->cs].op);
			printf("inst= %d\t\top= %d\n", mem[numlines + p1->cs].inst, mem[numlines + p1->cs].op);
			numlines++;
		}
		
		p1->ready = 1;
		printf("Rodando!\n\n");
	
		while(1)
		{
			//MUTEX
			pthread_mutex_lock(&runningMutex);
				if(running == p1)
				{
					printf("PC: %d\t CS: %d\t DS: %d\t ACC: %d\n", running->pc, running->cs, running->ds, running->acc);
					if(run_line() == PROG_END) break;
					running->pc++;
				}
			pthread_mutex_unlock(&runningMutex);
			//MUTEX END
		}
		//Terminou execução
		
		pthread_mutex_lock(&allocatorMutex);
			if(free_memory_block(running->block) == UNALLOCATED_MEM)
			{
				printf("Memória já foi desalocada. Algo muito errado aconteceu.\n");
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
			printf("Arquivo inválido!\n");
			exit(-1);
		}
	
		p2->tty = tty2;
		p2->ready = 0;
		
		pthread_mutex_lock(&allocatorMutex);
			if(allocate_block() == OUT_OF_MEMORY)
			{
				printf("SEM MEMÓRIA\n");
				continue;
			}
		pthread_mutex_unlock(&allocatorMutex);
			
		//Carregar programa na memória.
		while(!feof(f))
		{
			fscanf(f, "%d %d", &mem[numlines + p2->cs].inst, &mem[numlines + p2->cs].op);
			printf("inst= %d\t\top= %d\n", mem[numlines + p2->cs].inst, mem[numlines + p2->cs].op);
			numlines++;
		}
		
		p2->ready = 1;
		printf("Rodando!\n\n");
	
		while(1)
		{
			//MUTEX
			pthread_mutex_lock(&runningMutex);
				if(running == p2)
				{
					printf("PC: %d\t CS: %d\t DS: %d\t ACC: %d\n", running->pc, running->cs, running->ds, running->acc);
					if(run_line() == PROG_END) break;
					running->pc++;
				}
			pthread_mutex_unlock(&runningMutex);
			//MUTEX END
		}
		//Terminou execução
		
		pthread_mutex_lock(&allocatorMutex);
			if(free_memory_block(running->block) == UNALLOCATED_MEM)
			{
				printf("Memória já foi desalocada. Algo muito errado aconteceu.\n");
				continue;
			}
		pthread_mutex_unlock(&allocatorMutex);
	}
}