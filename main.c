/************
** ENTRADA  *
************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "cpu.h"
#include "memory.h"
#include "globals.h"

unsigned char pc;
unsigned char cs;
unsigned char ds;
char acc;

pthread_t tid0, tid1, tid2;

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
	
		//Carregar programa na memória.
		while(!feof(f))
		{
			fscanf(f, "%d %d", &mem[numlines].inst, &mem[numlines].op);
			fprintf(tty0, "i= %d\to= %d\n", mem[numlines].inst, mem[numlines].op);
			numlines++;
		}
	
		printf("Rodando!\n\n");
	
		//Run program.
		//Setar os registradores do programa rodando. Isto vai para uma função quando o gerenciador de memória funcionar.
		running->tty = tty0;
		running->acc = 0;
		running->pc = 0;
		running->cs = 0;
		running->ds = 128;
	
		for(i = 0; i <= numlines - 1; i++)
		{
			fprintf(tty0, "Register dump!\n");
			fprintf(tty0, "PC: %d\t CS: %d\t DS: %d\t ACC: %d\n", running->pc, running->cs, running->ds, running->acc);
			fprintf(tty0, "line %d: ", i);
			run_line();
			running->pc++;
			fprintf(tty0, "\n");
		}
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
	
		//Run program.
		//Setar os registradores do programa rodando. Isto vai para uma função quando o gerenciador de memória funcionar.
		running->tty = tty1;
		running->acc = 0;
		running->pc = 0;
		running->cs = 0;
		running->ds = 128;
	
		//Carregar programa na memória.
		while(!feof(f))
		{
			fscanf(f, "%d %d", &mem[numlines + running->pc].inst, &mem[numlines + running->pc].op);
			fprintf(tty1, "i= %d\to= %d\n", mem[numlines + running->pc].inst, mem[numlines + running->pc].op);
			numlines++;
		}
	
		printf("Rodando!\n\n");

	
		for(i = 0; i <= numlines - 1; i++)
		{
			fprintf(tty1, "Register dump!\n");
			fprintf(tty1, "PC: %d\t CS: %d\t DS: %d\t ACC: %d\n", running->pc, running->cs, running->ds, running->acc);
			fprintf(tty1, "line %d: ", i);
			run_line();
			running->pc++;
			fprintf(tty1, "\n");
		}
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
	
		//Run program.
		//Setar os registradores do programa rodando. Isto vai para uma função quando o gerenciador de memória funcionar.
		running->tty = tty2;
		running->acc = 0;
		running->pc = 0;
		running->cs = 0;
		running->ds = 128;
	
		//Carregar programa na memória.
		while(!feof(f))
		{
			fscanf(f, "%d %d", &mem[numlines + running->pc].inst, &mem[numlines + running->pc].op);
			fprintf(tty2, "i= %d\to= %d\n", mem[numlines + running->pc].inst, mem[numlines + running->pc].op);
			numlines++;
		}
	
		printf("Rodando!\n\n");
	
		for(i = 0; i <= numlines - 1; i++)
		{
			fprintf(tty2, "Register dump!\n");
			fprintf(tty2, "PC: %d\t CS: %d\t DS: %d\t ACC: %d\n", running->pc, running->cs, running->ds, running->acc);
			fprintf(tty2, "line %d: ", i);
			run_line();
			running->pc++;
			fprintf(tty2, "\n");
		}
	}
}