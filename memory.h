#ifndef MEMORY_H
#define MEMORY_H

/*********************
** STRUCT DA MEMORIA *
*********************/

/*linha do programa, contem operacao e operando*/
typedef struct line 
{
	unsigned char inst; /* Caso seja segmento de dados, guarda o dado */
	unsigned char op;
} line;

extern line mem[256];  /* Nosso bloco de memoria */

#endif /*MEMORY_H*/
