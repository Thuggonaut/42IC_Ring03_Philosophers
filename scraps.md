

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
- used to synchronize the parent and child processes.

Syntax: 
```
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *status, int options);
```

Parameters:
1. `pid`: 
	- The process ID to wait for. 
	- Use -1 to wait for any child process, or a specific PID to wait for a particular child process.
2. `status`: 
	- A pointer to an integer where the exit status of the child process will be stored.
3. `options`: 
	- Additional options for controlling the behavior of waitpid. 
	- Commonly used options include WNOHANG (non-blocking) and WUNTRACED (report status of stopped child processes).

Return value: 
- On success, returns the process ID of the terminated child process.
- On failure, returns -1, and sets errno to indicate the error.

Example: 
```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) 
{
	pid_t child_pid = fork();

	// Code executed by the parent process
	printf("Parent process (PID: %d) waiting for the child to finish.\n", getpid());

	int status;
	pid_t terminated_pid = waitpid(child_pid, &status, 0);

	if (terminated_pid == -1) 
	{
		perror("Waitpid failed");
		return (-1);
	}
	
	printf("Child process (PID: %d) exited with status: %d\n", terminated_pid, WEXITSTATUS(status));
	printf("Parent process exiting.\n");

	return (0);
}
```

#### 🔸 **14. sem_open():**
- used for creating or opening a named semaphore. 
- Semaphores are synchronization mechanisms that help coordinate access to shared resources or critical sections of code among multiple processes.

Syntax:
```
#include <semaphore.h>

sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
```

Parameters:
1. `name`: 
	- A string representing the name of the semaphore. 
	- This can be a name that begins with a slash ('/') character or a name that does not contain a slash. 
	- The name is used to identify the semaphore among processes.
2. `oflag`: 
	- The flags specifying the operation to be performed. 
	- It can include one or more of the following:
		- `O_CREAT`: Create the semaphore if it does not exist.
		- `O_EXCL`: If O_CREAT is also specified and the semaphore already exists, return an error.
		- `O_RDWR`: Open the semaphore for reading and writing.
3. `mode`: 
	- The file permissions to be set if `O_CREAT` is specified. 
	- It is specified in octal mode (e.g., 0644).

4. `value`: 
	- The initial value for the semaphore.

Return value:
- On success, a pointer to the semaphore is returned.
- On failure, SEM_FAILED is returned, and errno is set to indicate the error.

Example:
```
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    sem_t *my_semaphore;

    // Open or create a semaphore named "my_sem" with an initial value of 1
    my_semaphore = sem_open("/my_sem", O_CREAT | O_EXCL, 0644, 1);

    if (my_semaphore == SEM_FAILED) 
	{
        perror("Error creating/opening semaphore");
        exit(EXIT_FAILURE);
    }

    // Use the semaphore...

    // Close and unlink the semaphore when done
    sem_close(my_semaphore);
    sem_unlink("/my_sem");

    return (0);
}
```

#### 🔸 **15. sem_close():** 
- used to close a named semaphore that was previously opened with sem_open. Closing a semaphore is necessary to release system resources associated with the semaphore.

Syntax:
```
#include <semaphore.h>

int sem_close(sem_t *sem);
```

Parameters:
1. `sem`: 
	- A pointer to the semaphore object that you want to close.

Return value:
- Returns 0 on success.
- Returns -1 on failure, and sets errno to indicate the error.

Example:
```
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    sem_t *my_semaphore;

    // Open or create a semaphore named "my_sem" with an initial value of 1
    my_semaphore = sem_open("/my_sem", O_CREAT | O_EXCL, 0644, 1);

    if (my_semaphore == SEM_FAILED) 
	{
        perror("Error creating/opening semaphore");
        exit(EXIT_FAILURE);
    }

    // Use the semaphore...

    // Close and unlink the semaphore when done
    sem_close(my_semaphore);
    sem_unlink("/my_sem");

    return (0);
}
```


#### 🔸 **16. sem_wait():** 
- used to decrement the value of the semaphore, blocking the calling thread if the semaphore's value is currently zero. 
- It is typically used to acquire access to a shared resource or to enter a critical section.

Syntax:
```
#include <semaphore.h>

int sem_wait(sem_t *sem);
```

Parameters:
1. `sem`: 
	- A pointer to the semaphore object to wait on.

Return value:
- On success, sem_wait() returns 0.
- On failure, it returns -1, and sets errno to indicate the error.

Example:
```
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void *thread_function(void *arg) 
{
    //Wait for the semaphore to be available
    sem_wait(&semaphore);

    //Critical section: shared resource access
    printf("Thread has acquired the semaphore\n");

    //Release the semaphore
    sem_post(&semaphore);

    pthread_exit(NULL);
}

int main(void) 
{
    pthread_t thread_id;
    
    //Initialize the semaphore with an initial value of 1
    sem_init(&semaphore, 0, 1);

    //Create a new thread
    pthread_create(&thread_id, NULL, thread_function, NULL);

    //Wait for the thread to finish
    pthread_join(thread_id, NULL);

    //Destroy the semaphore
    sem_destroy(&semaphore);

    return (0);
}
```

#### 🔸 **17. sem_post():** 
- used to increment the value of the semaphore, allowing other threads waiting on the semaphore to proceed. 
- It is typically used to release a resource or signal the availability of a shared resource after it has been used.

Syntax:
```
#include <semaphore.h>

int sem_post(sem_t *sem);
```

Parameters:
1. `sem`: 
	- A pointer to the semaphore object to be incremented.

Return value:
- On success, sem_post() returns 0.
- On failure, it returns -1, and sets errno to indicate the error.

Example:
```
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void *thread_function(void *arg) 
{
    //Wait for the semaphore to be available
    sem_wait(&semaphore);

    //Critical section: shared resource access
    printf("Thread has acquired the semaphore\n");

    //Release the semaphore
    sem_post(&semaphore);

    pthread_exit(NULL);
}

int main(void) 
{
    pthread_t thread_id;
    
    //Initialize the semaphore with an initial value of 1
    sem_init(&semaphore, 0, 1);

    //Create a new thread
    pthread_create(&thread_id, NULL, thread_function, NULL);

    //Wait for the thread to finish
    pthread_join(thread_id, NULL);

    //Destroy the semaphore
    sem_destroy(&semaphore);

    return (0);
}
```

#### 🔸 **18. sem_unlink():** 
- used to unlink (delete) a named semaphore. 

Syntax:
```
#include <semaphore.h>

int sem_unlink(const char *name);
```

Parameters:
1. `name`: 
	- A pointer to a null-terminated string containing the name of the semaphore to be unlinked. 
	- This name should follow the naming conventions specified by the system.

Return value:
- Returns 0 on success.
- Returns -1 if an error occurs, and sets errno to indicate the error.

Example:
```
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int main(void) 
{
    // Name of the semaphore to unlink
    const char *semaphore_name = "/my_semaphore";

    // Unlink the semaphore
    if (sem_unlink(semaphore_name) == -1) 
	{
        perror("Error unlinking semaphore");
        return (-1);
    }

    printf("Semaphore unlinked successfully.\n");
    return (0);
}
```