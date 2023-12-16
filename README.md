Philosophers

## To succeed this assignment:
- One or more philosophers sit at a round table.
	- There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep.
	- While they are eating, they are not thinking nor sleeping;
	- while thinking, they are not eating nor sleeping;
	- and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, 
	- they put their forks back on the table and start sleeping. 
	- Once awake, they start  thinking again. 
	- The simulation stops when a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!


## Your(s) program(s) should take the following arguments:
1. number_of_philosophers 
2. time_to_die 
3. time_to_eat 
4. time_to_sleep
5. number_of_times_each_philosopher_must_eat

1. `number_of_philosophers`: 
	- The number of philosophers and also 
	- the number of forks.
2. `time_to_die` (in milliseconds): 
	- If a philosopher didn’t start eating `time_to_die` milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
3. `time_to_eat` (in milliseconds): 
	- The time it takes for a philosopher to eat.
	- During that time, they will need to hold two forks.
4. `time_to_sleep` (in milliseconds): 
	- The time a philosopher will spend sleeping.
5. `number_of_times_each_philosopher_must_eat` (optional argument): 
	- If all philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times, the simulation stops. 
	- If not specified, the simulation stops when a philosopher dies.

- Each philosopher has a number ranging from `1` to `number_of_philosophers`.
- Philosopher number `1` sits next to philosopher number `number_of_philosophers`.
	- Any other philosopher number `N` sits between philosopher number `N - 1` and philosopher number `N + 1`.

## About the logs of your program:
- Any state change of a philosopher must be formatted as follows:
	- `timestamp_in_ms` X has taken a fork
	- `timestamp_in_ms` X is eating
	- `timestamp_in_ms` X is sleeping
	- `timestamp_in_ms` X is thinking
	- `timestamp_in_ms` X died
- Replace `timestamp_in_ms` with the current timestamp in milliseconds and `X` with the philosopher number.
- A displayed state message should not be mixed up with another message.
- A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
- Again, philosophers should avoid dying!
- Your program must not have any data races.


## Mandatory rules:
- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. 
	- Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. 
	- If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.


## Bonus rules:
- All the forks are put in the middle of the table.
- They have no states in memory but the number of available forks is represented by a semaphore.
- Each philosopher should be a process. But the main process should not be a philosopher.


## What is a thread?

Single threaded program
- one sequence of statements that executes over time [img]

Multi threaded program
- multiple sequence of statements that executes over the same period of time
- Parallel execution:
	- Not always possible to execute threads in parallel due to hard/software [img]

- Concurrent execution when parallel not possible:
	- CPU switches back and forth bewtween multiple threads
	- only one thread is executed at any given time [img]

Threads can improve performance. 

## How to create a thread?

- We use the <pthread.h> library.
	1.  Call `pthread_create()` to create a thread.
	2.  Give `pthread_create()` a function to run.
		- the function will run in it's own thread. 
	3. Call `pthread_join()` to join the newly created thread back to the main thread. 
		- `pthread_join()` by the time it runs, will pause and wait until the created thread finishes execution if it hasn't already [img]


## What are mutexes?


## What are data races?


## What is a semaphore?


## External functions to learn:

1. memset
1. usleep
1. gettimeofday
1. pthread_create
1. pthread_detach
1. pthread_join
1. pthread_mutex_init
1. pthread_mutex_destroy
1. pthread_mutex_lock
1. pthread_mutex_unlock

## Bonus external functions:
1. fork
1. kill
1. exit
1. waitpid
1. sem_open
1. sem_close
1. sem_post
1. sem_wait
1. sem_unlink


### memset
- Used to initialize or clear blocks of memory to a specific value

Syntax:
```
void *memset(void *ptr, int value, size_t num);
```
Parameters:
1. `ptr`: 
	- Pointer to the memory block to fill.
2. `value`: 
	- Value to be set. 
	- The value is passed as an int, but memset interprets it as an unsigned char, allowing you to set any byte value (0 to 255).
3. `num`: 
	- Number of bytes to be set to the specified value.

Return value:
- a pointer to the memory area ptr.

Example:
```
#include <stdio.h>
#include <string.h>

int main(void) 
{
    char str[20];

    // Set the first 10 bytes of the 'str' array to the ASCII value of 'A'
    memset(str, 'A', 10);

    printf("After memset: %s\n", str);
    return (0);
}
```

### usleep


### gettimeofday

### pthread_create
- Used to create a new thread within a program.

Syntax:
```
int	pthread_create(pthread_t *thread_id, const pthread_attr_t *attr,
					void *(*thread_function) (void *), void *arg);
```
Parameters:
1. `thread_id`: 
	- A pointer to a pthread_t variable that stores the ID of the newly created thread.

2. `attr`: 
	- A pointer to a pthread_attr_t structure that specifies various attributes for the new thread. 
	- If `NULL` is passed, the default attributes are used.

3. `thread_function`: 
	- A pointer to the function that will be executed by the new thread. 
	- It takes a single argument of type `void*` and 
	- Must return a `void*`.

4. `arg`: 
	- The argument to be passed to the thread_function function. This can be used to pass data or information to the newly created thread.

Return value:
- If the thread creation is successful, pthread_create returns 0.
- If there is an error, a non-zero error code is returned.

Example:
```
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

	// Create a new thread, accessing the memory address of value1&2, casting it to 'void *'
	// Call the thread_function twice, with two different values, running in two different threads
	pthread_create(&id_1, NULL, thread_function, (void *) &value1);
	pthread_create(&id_2, NULL, thread_function, (void *) &value2);

	// Wait for the thread to finish
	pthread_join(id_1, NULL);
	pthread_join(id_2, NULL);

	printf("Main thread exiting.\n");
	return (0);
}
```

### pthread_detach
### pthread_join
### pthread_mutex_init
### pthread_mutex_destroy
### pthread_mutex_lock
### pthread_mutex_unlock
### fork
### kill
### exit
### waitpid
### sem_open
### sem_close
### sem_post
### sem_wait
### sem_unlin


# References:

**Introduction To Threads (pthreads)**
- An introduction on how to use threads in C with the pthread.h library (POSIX thread library)
- https://www.youtube.com/watch?v=ldJ8WGZVXZk

**Unix Threads in C**
- Playlist of all things threads related
- https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=0QgGb_xmrDESzk62 

**The dining Philosophers in C**
- Oceano's walkthrough of the project
- https://youtu.be/zOpzGHwJ3MU?si=-C45_b4npZc_n4p6 