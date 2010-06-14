/*******************************
** GRANDE SWITCH D'O QUE FAZER *
*******************************/
#include <stdio.h>
#include "globals.h"
#include "defines.h"
#include "cpu.h"

line mem[256];	        /* Nosso bloco de memoria */
char acc;				/* Registrador acc (acumulador) */
unsigned char pc;		/* Registrador pc  (Program Counter) */
unsigned char ds;		/* Registrador ds  (Data Section) */
unsigned char cs;		/* Registrador cs  (Code Section) */

process running;

int run_line()
{
	switch(mem[running->pc + running->cs].inst)
	{
		case 0:
			/* running->acc = running->acc + op */
			running->acc = running->acc + mem[mem[running->pc + running->cs].op + running->ds].inst;
			break;
		case 1:
			/* running->acc = running->acc - op */
			running->acc = running->acc - mem[mem[running->pc + running->cs].op + running->ds].inst;
			break;
		case 2:
			/* running->acc = running->acc * op */
			running->acc = running->acc * mem[mem[running->pc + running->cs].op + running->ds].inst;
			break;
		case 3:
			/* running->acc = running->acc / op */
			running->acc = running->acc / mem[mem[running->pc + running->cs].op + running->ds].inst;
			break;
		case 4:
			/* running->acc = op */
			running->acc = mem[mem[running->pc + running->cs].op + running->ds].inst;
			break;
		case 5:
			/* op = running->acc */
			mem[mem[running->pc].op + running->ds].inst = running->acc;
			break;
		case 6:
			//NOP	
			break;
		case 7:
			//Se running->acc > 0 salta para [op]
			if(running->acc > 0) running->pc = mem[running->pc + running->cs].op;
			break;
		case 8:
			//Se running->acc < 0 salta para [op]
			if(running->acc < 0) running->pc = mem[running->pc + running->cs].op;
			break;
		case 9:
			//Se running->acc == 0 salta para [op]
			if(running->acc == 0) running->pc = mem[running->pc + running->cs].op;			
			break;
		case 10:
			//In para [op]
			fprintf(running->tty, "$< ");
			fscanf(running->tty, "%d", &mem[mem[running->pc + running->cs].op + running->ds].inst);
			break;
		case 11:
			//Out de [op]
			fprintf(running->tty, "$> %d", mem[mem[running->pc + running->cs].op + running->ds].inst);
			break;
		case 12:
			fprintf(running->tty, "Fim de execução\n");
			return PROG_END;
			break;
		default:
			printf("INSTRUCAO INVALIDA!\n");
			return INVINST_FAIL;
	}
	return 0;
}
