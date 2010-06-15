#include <pthread.h>

pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv)
{
	pthread_mutex_lock(&mutx);
	pthread_mutex_lock(&mutx);
	
	return 0;
}