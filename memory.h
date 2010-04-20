/*********************
** STRUCT DA MEMORIA *
*********************/

/*linha do programa, contem operacao e operando*/
struct line 
{
	char inst;
	char op;
};

/*memoria da maquina virtual, 256 posições*/
struct memory
{
	struct line[256];
};
