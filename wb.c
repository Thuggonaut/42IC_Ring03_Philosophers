#include <pthread.h>
#include <stdio.h>

void	*thread_function(void *arg) 
{
	// Casting the void pointer *arg being passed in, to 'long *'
	long	*arg_num = (long *)(arg); 

	printf("Arg: %ld\n", *arg_num);
	return (NULL);
}

int main(void) 
{
	pthread_t	id_1;
	pthread_t	id_2; // Multiple threading
	
	// An example value we want to pass in thread_function via a pointer
	long		value1 = 1; 
	long		value2 = 2;

	// Create a new thread, accessing the memory address of value1, casting it to 'void *'
	pthread_create(&id_1, NULL, thread_function, (void *) &value1);
	pthread_create(&id_2, NULL, thread_function, (void *) &value2);

	// Wait for the thread to finish
	pthread_join(id_1, NULL);
	pthread_join(id_2, NULL);

	printf("Main thread exiting.\n");
	return (0);
}