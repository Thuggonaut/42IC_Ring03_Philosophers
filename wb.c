#include <stdio.h>
#include <unistd.h>

int main(void) {
    int	child1 = fork(); // First fork
    int	child2 = fork(); // Second fork
    
    printf("Hello world ID: %d, %d\n", child1, child2);
    return 0;
}

/*
//DEX TUTOR

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t	spoon[5]; //5 to include a variable for each spoon
void	*philos(void *n); //DEFINE
void	eat(int); //DEFINE

int		main(void)
{
	int			i = 0; //To keep track of the thread number
	int			n[5];
	pthread_t	p_t[5]; //One variable for each thread for each philosopher

	//Initialize every semaphore variable
	while (i < 5)
	{
		sem_init(&spoon[i], 0, 1); //Each spoon is initially free
		i++;
	}

	//Create a thread for each philosopher
	i = 0;
	while (i < 5)
	{
		n[i] = i;
		pthread_create(&p_t[i], NULL, philos, (void *)&n[i]); //The `void` will be the input for the philos() ft
		i++;
	}

	//Join each of the threads
	i = 0;
	while (i < 5)
	{
		pthread_join(p_t[i], NULL);
		i++;
	}		
}

void	*philos(void *n)
{
	int		ph = *(int *)n; //`n` value will be `i`

	printf("Philosopher %d wants to eat\n", ph);
	printf("Philosopher %d tries to pick up left spoon\n", ph);
	sem_wait(&spoon[ph]); //Ph will try to pick up the left spoon, and if successfull, continue
	
	printf("Philosopher %d picks up left spoon\n", ph);
	printf("Philosopher %d tries to pick up right spoon\n", ph);
	sem_wait(&spoon[(ph + 1) % 5]); //Ph will try to pick up the right spoon, and if successfull, continue

	printf("Philosopher %d picks up right spoon\n", ph);
	eat(ph); //Ph can eat now that left and right spoons have been gathered
	sleep(2); //The current thread sleeps, DEFINE
	printf("Philosopher %d has finished eating\n", ph);

	sem_post(&spoon[(ph + 1) % 5]); //Let the next ph know the current ph is putting down the right spoon
	printf("Philosopher %d puts down right spoon\n", ph);
	sem_post(&spoon[ph]); //Then puts down left spoon
	printf("Philosopher %d puts down left spoon\n", ph);

	return (NULL);
}

void	eat(int ph)
{
	printf("Philosopher %d begins to eat\n", ph);
}



/*
int	i, n[5];
pthread_t	p_t[5];

for (i = 0; i < 5; i++)
	sem_init(&spoon[i], 0, 1);

for (i = 0; i < 5; i++)
{
	n[i] = i;
	pthread_create(&p_t[i], NULL, philos, (void *)&n[i]);
}

for (i = 0; i < 5; i++)
{
	pthread_join(p_t[i], NULL);
}

*/