#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t			forkk[5]; //5 to include a variable for each fork
pthread_mutex_t mutex; //Mutex for critical sections

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
		sem_init(&forkk[i], 0, 1); //Each fork is initially free
		i++;
	}

	//Initialize mutex
	pthread_mutex_init(&mutex, NULL); 

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

	//Destroy mutex
	pthread_mutex_destroy(&mutex); 

	return (0);
}

void	*philos(void *n)
{
	int		ph = *(int *)n; //`n` value will be `i`
		
	//Ensure that philosophers wait their turn to pick up forks
	pthread_mutex_lock(&mutex);

	printf("Philosopher %d is thinking\n", ph);
	sem_wait(&forkk[ph]); //Ph will try to pick up the left fork, and if successful, continue

	printf("Philosopher %d has taken a fork\n", ph);
	//printf("Philosopher %d tries to pick up right fork\n", ph);
	sem_wait(&forkk[(ph + 1) % 5]); //Ph will try to pick up the right fork, and if successful, continue

	//printf("Philosopher %d picks up right fork\n", ph);
	pthread_mutex_unlock(&mutex); //Unlock critical section

	eat(ph); //Ph can eat now that left and right forks have been gathered
	sleep(2); //The current thread sleeps, to allow the other threads to execute at the same time

	sem_post(&forkk[(ph + 1) % 5]); //Let the next philosopher know the current philosopher is putting down the right fork
	sem_post(&forkk[ph]); //Then puts down left fork

	printf("Philosopher %d is sleeping\n", ph);
	//printf("Philosopher %d puts down left fork\n", ph);

	return (NULL);
}

void	eat(int ph)
{
	printf("Philosopher %d is eating\n", ph);
}
