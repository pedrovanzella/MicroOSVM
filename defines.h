#ifndef DEFINES_H
#define DEFINES_H

/**********
* DEFINES *
**********/

#define INVINST_FAIL -1
#define PROG_END		 1

typedef struct
{
	char acc;				/* Registrador ACC (acumulador) */
	unsigned char pc;		/* Registrador PC  (Program Counter) */
	unsigned char ds;		/* Registrador DS  (Data Section) */
	unsigned char cs;		/* Registrador CS  (Code Section) */
	
	FILE* tty;			    /* Nome do terminal */	
} process;

#endif /*DEFINES_H*/
