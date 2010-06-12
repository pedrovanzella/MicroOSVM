#ifndef GLOBALS_H
#define GLOBALS_H

/***********
** GLOBAIS *
***********/

#include "memory.h"
#include "defines.h"

extern char acc;		/* Registrador ACC (acumulador) */
extern unsigned char pc;		/* Registrador PC  (Program Counter) */
extern unsigned char ds;		/* Registrador DS  (Data Section) */
extern unsigned char cs;		/* Registrador CS  (Code Section) */

extern process running;

#endif /*GLOBAIS_H*/
