/*******************************
** GRANDE SWITCH D'O QUE FAZER *
*******************************/
#include <stdio.h>
#include "globals.h"
#include "defines.h"

int run_line()
{
	switch(mem[pc].inst)
	{
		case 00:
			acc = acc + mem[mem[pc].op + ds] /* ACC = ACC + op */
			break;
		case 01:
			acc = acc - mem[mem[pc].op + ds] /* ACC = ACC - op */
			break;
		case 02:
			acc = acc * mem[mem[pc].op + ds] /* ACC = ACC * op */
			break;
		case 03:
			acc = acc / mem[mem[pc].op + ds] /* ACC = ACC / op */
			break;
		case 04:
			acc = mem[mem[pc].op + ds] /* ACC = op */
			break;
		case 05:
			mem[mem[pc].op + ds] = acc /* op = ACC */
			break;
		case 06:
			
			break;
		case 07:
			
			break;
		case 08:
			
			break;
		case 09:
			
			break;
		case 10:
			
			break;
		case 11:
			
			break;
		case 12:
			return PROG_END
			break;
		default:
			printf("INSTRUCAO INVALIA!\n");
			return INVINST_FAIL
	}
	return 0;
}
