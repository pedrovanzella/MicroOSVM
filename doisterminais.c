#include <stdio.h>
#include <pthread.h>

pthread_t tid1, tid2 ;

FILE *Term1, *Term2 ;

void *t1 () {
  int a ;

  for (;;) {
    fprintf (Term1, ">>") ;
    fprintf (Term1, "Digite um valor inteiro\n") ;
    fscanf (Term1, "%d", &a) ;
    fprintf (Term1, "Valor lido: %d\n", a) ;
    }
}

void *t2 () {
  int a ;
  for (;;) {
    fprintf (Term2, ">>") ;
    fprintf (Term2, "Digite um valor inteiro\n") ;
    fscanf (Term2, "%d", &a) ;
    fprintf (Term2, "Valor lido: %d\n", a) ;
    }
}

int main (int argc, char **argv) {

  
   printf ("Vou abrir Term1\n") ;
   Term1 = fopen (argv[1], "a+" ) ;
   printf ("Vou abrir Term2\n") ;
   Term2 = fopen (argv[2], "a+" ) ;
   printf ("Vou criar as threads\n") ;
   pthread_create(&tid1,NULL,t1, NULL);
   pthread_create(&tid2,NULL,t2, NULL);

   printf ("threads criadas\n") ;
   pthread_join(tid1, NULL) ;
   pthread_join(tid2, NULL) ;

}

