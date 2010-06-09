/*******************************
** GRANDE SWITCH D'O QUE FAZER *
*******************************/
#include <stdio.h>
#include "globals.h"
#include "defines.h"
#include "cpu.h"

line mem[256];		        /* Nosso bloco de memoria */
unsigned char acc;		/* Registrador ACC (acumulador) */
unsigned char pc;		/* Registrador PC  (Program Counter) */
unsigned char ds;		/* Registrador DS  (Data Section) */
unsigned char cs;		/* Registrador CS  (Code Section) */

int run_line()
{
	switch(mem[pc + cs].inst)
	{
		case 0:
			/* ACC = ACC + op */
			acc = acc + mem[mem[pc + cs].op + ds].inst;
			break;
		case 1:
			/* ACC = ACC - op */
			acc = acc - mem[mem[pc + cs].op + ds].inst;
			break;
		case 2:
			/* ACC = ACC * op */
			acc = acc * mem[mem[pc + cs].op + ds].inst;
			break;
		case 3:
			/* ACC = ACC / op */
			acc = acc / mem[mem[pc + cs].op + ds].inst;
			break;
		case 4:
			/* ACC = op */
			acc = mem[mem[pc + cs].op + ds].inst;
			break;
		case 5:
			/* op = ACC */
			mem[mem[pc].op + ds].inst = acc;
			break;
		case 6:
			//Inválido	
			break;
		case 7:
			//Se ACC > 0 salta para [op]
			
			break;
		case 8:
			//Se ACC < 0 salta para [op]
			
			break;
		case 9:
			//Se ACC == 0 salta para [op]
			
			break;
		case 10:
			//In para [op]
			
			break;
		case 11:
			//Out de [op]
			
			break;
		case 12:
			return PROG_END;
			break;
		default:
			printf("INSTRUCAO INVALIDA!\n");
			return INVINST_FAIL;
	}
	return 0;
}
