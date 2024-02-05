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


## What are data races?
- A data race is an instance of a race condition where multiple threads compete to access and modify shared data (variable or state) at the same time, leading to unpredictable outcomes.
- A race condition is when a program depends on the timing or order of events, leading to issues.
	- For instance, in a multithreaded environment, a data race may occur when multiple threads attempt to execute a function that involves shared variables. This simultaneous access can lead to inconsistencies, causing the final value of a variable to be out of sync with the expected result due to the unpredictable interleaving of thread executions. 
- Proper synchronization mechanisms such as mutexes or semaphores are essential to prevent race conditions.


## What are mutexes?
- Short for mutual exclusion, a mutex is a synchronization mechanism to control access to shared resources, allowing only one thread or process at a time to execute a critical section of code.
- We can allow one thread to access a section of code (e.g. a thread function) at a time, by locking it. This way, only one thread can execute said code at any given time. 
	- We create a lock before the citical code
	- And release the lock after the critical code is done executing.
	- What happens then, is when the first thread reaches the lock in the code, that thread aquires the lock. 
	- Any subsequent threads when reaching this lock, will pause, and wait until the lock has been released, in order to aquire it. 
- Basically, how a mutex works is, a thread will aquire a lock, run the execution of the code, then release the lock when done. 

Example of using a mutex:
1. In main() We make a mutex variable;
2. In main() Initialize the mutex;
3. In main() Destroy the mutex when done;
4. In thread function() Use the mutex to create the lock;
5. In thread function() Release the lock when done executing;
```
pthread_mutex_t mutex; //Variable 'mutex'

pthread_mutex_init(&mutex, NULL); //Initialize 'mutex' taking in a pointer to our mutex variable, and NULL (default configuration values)

pthread_mutex_destroy(&mutex); //When we're done with it, destroy it

//Inside a function or block of code, create a lock
pthread_mutex_lock(&mutex);

//After the code execution, still inside the function or code block, release the lock
pthread_mutex_unlock(&mutex);
```
- What happens is, the function is running at the same time in multiple threads:
	- One thread will reach the lock statement first, aquire the lock, run the code, then unlock.
	- Meanwhile, another thread will reach the lock statement, but it will pause, and wait for the lock to be released.
	- Once the next thread aquires the lock, it'll execute the code, with the updated variables/data. 


## What are semaphores?
- Semaphores are counters that control access to a resource with an arbitrary number of permits. 
- They can be used to limit the number of threads that can access a resource simultaneously.


## External functions to learn:

1. memset
2. usleep
3. gettimeofday
4. pthread_create
5. pthread_detach
6. pthread_join
7. pthread_mutex_init
8. pthread_mutex_destroy
9. pthread_mutex_lock
10. pthread_mutex_unlock

## Bonus external functions:
11. fork
12. kill
13. waitpid
14. sem_open
15. sem_close
16. sem_post
17. sem_wait
18. sem_unlink

#### 🔸 **1. memset():**
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
- A pointer to the memory area ptr.

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

#### 🔸 **2. usleep():**
- used to suspend the execution of a program to introduce a delay for a specified number of microseconds.

Syntax:
```
int usleep(useconds_t microseconds);
```
Parameters:
- `microseconds`:
	- specifies the number of microseconds the program should sleep.

Return Value:
- Returns 0 if the execution was successful (execution successfully suspended) or -1 if there was an error.

Example:
```
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(void) 
{
	printf("Sleeping for 2 seconds...\n");

	int result = usleep(2000000);

	if (result == 0) 
		printf("Woke up after sleeping.\n");
	else 
	{
		perror("Error in usleep");
		return (-1);
	}
	return (0);
}
```

#### 🔸 **3. gettimeofday():**
- Used to obtain the current time

Syntax:
```
int gettimeofday(struct timeval *tv, struct timezone *tz);
```
Parameters:
1. `tv`: 
	- A pointer to a struct timeval that will store the current time (including seconds and microseconds).

2. `tz`: 
	- (Deprecated and ignored on many systems) A pointer to a struct timezone that was used to store the timezone information. 
	- **It's generally recommended to pass NULL for this parameter.**

Return value:
- Returns 0 if the execution was successful (execution successfully suspended) or -1 if there was an error.

Example:
```
#include <stdio.h>
#include <sys/time.h>

int main(void) 
{
	struct timeval current_time;

	// Get the current time
	if (gettimeofday(&current_time, NULL) == 0) 
		printf("Current Time: %ld microseconds\n", current_time.tv_usec);
	else 
	{
		perror("Error getting time");
		return (-1);
	}
	return (0);
}
```

#### 🔸 **4. pthread_create():**
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

	return (0);
}
```

#### 🔸 **5. pthread_detach():** 
- Used to detach the newly created thread (thread_id). 
- This means that the resources associated with the thread will be automatically released when the thread exits, and the main thread does not need to explicitly join it.
- The difference is, `pthread_join()` is used when you want the main thread to wait for the completion of a specific thread. 
	- This is useful when the main thread needs the results produced by the other thread or when synchronization is necessary.
- Whereas, `pthread_detach()` is used when you want to detach a thread and let it run independently. 
	- The resources associated with the thread will be automatically released when the thread exits. 
	- This is useful when you don't need to wait for the thread to finish and don't need its return value.

Syntax:
```
int pthread_detach(pthread_t thread_id);
```

Parameters:
1. `thread_id`: 
	- The ID of the thread to be joined.

Return value:
- If successful, pthread_detach returns 0.
- If an error occurs, a non-zero error code is returned.

Example:
```
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_function(void *arg) 
{
	// Thread logic goes here
	printf("Thread is running...\n");
	usleep(200000);
	printf("Thread is done.\n");

	pthread_exit(NULL);
}

int main(void) 
{
	pthread_t thread_id;
		
	pthread_create(&thread_id, NULL, thread_function, NULL);

	// Detach the thread to allow it to run independently
	pthread_detach(thread_id);

	printf("Main thread is continuing its execution...\n");

	// Main thread doesn't need to join the detached thread

	return (0);
}
```

#### 🔸 **6. pthread_join():** 
- Used to wait for the thread with ID thread_id to finish its execution.

Syntax:
```
int pthread_join(pthread_t thread_id, void **retval);
```

Parameters:
1. `thread_id`: 
	- The ID of the thread to be joined.

2. `retval`: 
	- A pointer to a location where the exit status of the joined thread can be stored. - This is an optional parameter. If you're not interested in the exit status, you can pass `NULL`.

Return value:
- If successful, pthread_join() returns 0.
- On failure, it returns an error code.

Example:
- See example in **4. pthread_create()**


#### 🔸 **7. pthread_mutex_init():** 
- Used to initialize a mutex

Syntax:
```
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
```

Parameters:
1. `mutex`: 
	- A pointer to a pthread_mutex_t variable that will be initialized.

2. `attr`: 
	- A pointer to a pthread_mutexattr_t structure that specifies various attributes for the mutex. 
	- If `NULL` is passed, the default attributes are used.

Return value:
- If the mutex initialization is successful, pthread_mutex_init returns 0.
- If there is an error, a non-zero error code is returned.

Example:
```
#include <pthread.h>
#include <stdio.h>

int main(void) 
{
	//Declare mutex variable
	pthread_mutex_t my_mutex;

	// Initialize the mutex for synchronization
	pthread_mutex_init(&my_mutex, NULL);

	// Destroy the mutex when it's no longer needed
	pthread_mutex_destroy(&my_mutex);

	return (0);
}
```


#### 🔸 **8. pthread_mutex_destroy():**
- Used to destroy the mutex after it has been used

Syntax:
```
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

Parameters:
1. `mutex`: 
	- A pointer to the mutex object to be destroyed.

Return value:
- If the mutex is successfully destroyed, pthread_mutex_destroy returns 0.
- If an error occurs, a non-zero error code is returned.

Example:
```
#include <pthread.h>
#include <stdio.h>

void *thread_function(void *arg) 
{
	// Thread logic using the mutex goes here
	pthread_mutex_lock(&my_mutex);
	printf("Thread inside the critical section.\n");
	pthread_mutex_unlock(&my_mutex);

	pthread_exit(NULL);
}

int main(void) 
{
	//Declare mutex variable
	pthread_mutex_t my_mutex;

	// Initialize the mutex for synchronization
	pthread_mutex_init(&my_mutex, NULL);

	pthread_t thread_id;

	pthread_create(&thread_id, NULL, thread_function, NULL);

	// Thread function is called on &thread_id

	// Wait for the thread to finish
	pthread_join(thread_id, NULL);

	// Destroy the mutex when it's no longer needed
	pthread_mutex_destroy(&my_mutex);

	return (0);
}
```


#### 🔸 **9. pthread_mutex_lock():** 
- Used to lock the mutex before accessing and updating the shared data 

Syntax:
```
int pthread_mutex_lock(pthread_mutex_t *mutex);
```
Parameters:
1. `mutex`: 
	- A pointer to a pthread_mutex_t variable, representing the mutex object that you want to lock. 

Return value:
- If the mutex is successfully locked, pthread_mutex_lock() returns 0.
- If an error occurs, a non-zero error code is returned.

Example:
- See example in **8. pthread_mutex_destroy()**


#### 🔸 **10. pthread_mutex_unlock():** 
- Used to lock the mutex before accessing and updating the shared data 

Syntax:
```
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```
Parameters:
1. `mutex`: 
	- A pointer to the mutex object that was previously initialized.

Return value:
- If the mutex is successfully locked, pthread_mutex_lock() returns 0.
- If an error occurs, a non-zero error code is returned.

Example:
- See example in **8. pthread_mutex_destroy()**


#### 🔸 **11. fork():** 
- Used to create a new process (forking the execution line) at fork() by duplicating the existing one.
- The newly created process is called the child process.
- The child process then executes along side the main process (the parent process) at the same time. 
	- Let's say, we create a main(), and inside main(), somewhere we call fork().
	- Launching main will give us two processes: main() executing; and when fork() is called, we have the child process duplicating and executing with the parent.
- fork() returns us two process IDs (PID): of the main process, and of the child process (always 0). 
	- The value returned is how we distinguish which is parent ( value > 0) and which is child (value == 0).


Syntax:
```
#include <unistd.h>

pid_t fork(void);
```

Parameters:
- void

Return value:
- Returns a value in the parent process:
	- On success, the process ID (PID) of the child process is returned in the parent.
	- On failure, -1 is returned, and an error code is set in errno.
- In the child process the return value is always 0.

Example:
```
int main(void) 
{
    // Create a new child process by forking
	int	id = fork();

    if (id == -1) 
	{
        // Forking failed
        perror("Fork failed");
        return (-1);
    } 
	else if (id == 0)
        // Code executed by the child process
        printf("Hello from the child process! (PID: %d)\n", id);
    else 
        // Code executed by the parent process
        printf("Hello from the parent process! (PID: %d, Child PID: %d)\n", getpid(), id);

    return (0);
}
```

- What if we called fork() more than once in main?
	- it will give us 2^n (two to the power of n) processes where n is the number of fork() system calls. 
```
int main(void) 
{
	fork(); 
    fork(); 
    fork(); 
    printf("Hello world!\n");

    return (0);
}
```
- Output:
```
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
```


#### 🔸 **12. kill():** 
- used to send a signal to a process or a group of processes specified by the process ID.

Syntax:
```
int kill(pid_t pid, int sig)
```
Parameters:
1. `pid`: 
	- The process ID of the target process. It can take the following values:
		- Positive PID: 
			- Sends the signal to the process with the specified PID.
		- `0`: 
			- Sends the signal to all processes in the current process group.
		- `-1`: 
			- Sends the signal to all processes for which the calling process has permission to send signals, except for itself.
		- Negative PID: 
			- Sends the signal to all processes in the process group whose ID is the absolute value of pid.
2. `int sig`: 
	- This parameter is the signal number that you want to send. 
	- It's an integer representing the specific signal you wish to use. 
	- Common signals include SIGUSR1, SIGUSR2, SIGTERM, SIGKILL, and many more. 

Return value:
- The function returns 0 on success and -1 on error and sets errno to show that an error has occurred.

Example:
```
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) 
{
	pid_t target_pid = 1234; // Process ID

	// Send the SIGTERM signal to the target process
	if (kill(target_pid, SIGTERM) == 0) 
		printf("Signal sent successfully to process %d.\n", target_pid);
	else
	{
		perror("Error sending signal");
		return (-1);
	}
	return (0);
}
```

#### 🔸 **13. waitpid():** 
#### 🔸 **14. sem_open():** 
#### 🔸 **15. sem_close():** 
#### 🔸 **16. sem_post():** 
#### 🔸 **17. sem_wait():** 
#### 🔸 **18. psem_unlin():** 


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