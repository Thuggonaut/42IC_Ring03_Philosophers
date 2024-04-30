#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>

sem_t forkk; //Semaphore representing the forks

void philos(int); //Define

int main(void)
{
    pid_t pid[5]; //Process IDs for each philosopher

    //Initialize the semaphore representing the forks
    sem_init(&forkk, 0, 5); //5 forks initially available

    //Create a process for each philosopher
    pid_t parent_pid = getpid();
    int i = 0;
    while (i < 5)
    {
        pid[i] = fork();
        if (pid[i] == 0)
        {
            //Child process (philosopher)
            philos(i);
            exit(0); //Exit the child process after eating
        }
        else if (pid[i] < 0)
        {
            //Error handling for fork failure
            perror("fork");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    //Wait for all philosopher processes to finish
    int status;
    i = 0;
    while (i < 5)
    {
        waitpid(pid[i], &status, 0);
        i++;
    }

    return (0);
}

void philos(int ph)
{
    printf("Philosopher %d is thinking\n", ph);

    //Attempt to acquire two forks
    sem_wait(&forkk);
    printf("Philosopher %d has taken a fork\n", ph);
    sem_wait(&forkk);
    //printf("Philosopher %d picks up right fork\n", ph);

    //Philosopher is eating
    printf("Philosopher %d is eating\n", ph);
    sleep(2); 

    //Release the forks
    sem_post(&forkk);
    //printf("Philosopher %d puts down left fork\n", ph);
    sem_post(&forkk);
    //printf("Philosopher %d puts down right fork\n", ph);

    //Philosopher is done eating
    printf("Philosopher %d is sleeping\n", ph);
}
