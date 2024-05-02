# Bonus functions:

<table>
	<tr>
		<th> 🔸 fork() </th>
		<th> </th>
	</tr>
	<tr>
		<th> Use </th>
		<td> 

Create a new process (forking the execution line) at `fork()` by duplicating the existing one.
- The newly created process is called the child process.
- The child process then executes along side the main process (the parent process) at the same time. 
	- Let's say, we create a `main()`, and inside `main()`, somewhere we call `fork()`.
	- Launching main will give us two processes: `main()` executing; and when `fork()` is called, we have the child process duplicating and executing with the parent.
- `fork()` returns us two process IDs (`PID`): of the main process, and of the child process (always 0). 
	- The value returned is how we distinguish which is parent ( value > 0) and which is child (value == 0). 
</td>
	</tr>
	<tr>
		<th> Library & Syntax </th>
		<td> 

```c
<unistd.h>

pid_t fork(void);
``` 
</td>
		</tr>
		<tr>
		<th> Example </th>
		<td>

```c
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
- What if we called `fork()` more than once in main?
	- it will give us 2^n (two to the power of n) processes where n is the number of `fork()` system calls. 
```c
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
```bash
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
```
</td>
		</tr>
</table>

<table>
	<tr>
		<th> 🔸 kill() </th>
		<th> </th>
	</tr>
	<tr>
		<th> Use </th>
		<td> Ssend a signal to a process or a group of processes specified by the process ID </td>
	</tr>
	<tr>
		<th> Library & Syntax </th>
		<td> 

```c
<signal.h>

int kill(pid_t pid, int sig)
``` 
</td>
		</tr>
		<tr>
		<th> Example </th>
		<td>

```c
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
</td>
		</tr>
</table>

<table>
	<tr>
		<th> 🔸 waitpid() </th>
		<th> </th>
	</tr>
	<tr>
		<th> Use </th>
		<td> Synchronize the parent and child processes </td>
	</tr>
	<tr>
		<th> Library & Syntax </th>
		<td> 

```c
<sys/wait.h>

pid_t waitpid(pid_t pid, int *status, int options);
``` 
</td>
		</tr>
		<tr>
		<th> Example </th>
		<td>

```c
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
</td>
		</tr>
</table>

<table>
	<tr>
		<th> 🔸 sem_open() </th>
		<th> </th>
	</tr>
	<tr>
		<th> Use </th>
		<td> Create or open a named semaphore </td>
	</tr>
	<tr>
		<th> Library & Syntax </th>
		<td> 

```c
<semaphore.h>

sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
``` 
</td>
		</tr>
		<tr>
		<th> Example </th>
		<td>

```c
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
</td>
		</tr>
</table>

<table>
	<tr>
		<th> 🔸 sem_close() </th>
		<th> </th>
	</tr>
	<tr>
		<th> Use </th>
		<td> Close a named semaphore that was previously opened with sem_open() </td>
	</tr>
	<tr>
		<th> Library & Syntax </th>
		<td> 

```c

``` 
</td>
		</tr>
		<tr>
		<th> Example </th>
		<td>

```c
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
</td>
		</tr>
</table>

<table>
	<tr>
		<th> 🔸 sem_wait() </th>
		<th> </th>
	</tr>
	<tr>
		<th> Use </th>
		<td> Decrement the value of the semaphore, blocking the calling thread if the semaphore's value is currently zero </td>
	</tr>
	<tr>
		<th> Library & Syntax </th>
		<td> 

```c
<semaphore.h>

int sem_wait(sem_t *sem);
``` 
</td>
		</tr>
		<tr>
		<th> Example </th>
		<td>

```c
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
</td>
		</tr>
</table>

<table>
	<tr>
		<th> 🔸 sem_post() </th>
		<th> </th>
	</tr>
	<tr>
		<th> Use </th>
		<td> Increment the value of the semaphore, allowing other threads waiting on the semaphore to proceed </td>
	</tr>
	<tr>
		<th> Library & Syntax </th>
		<td> 

```c
<semaphore.h>

int sem_post(sem_t *sem);
``` 
</td>
		</tr>
		<tr>
		<th> Example </th>
		<td>

```c
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
</td>
		</tr>
</table>

<table>
	<tr>
		<th> 🔸 sem_unlink() </th>
		<th> </th>
	</tr>
	<tr>
		<th> Use </th>
		<td> Unlink (delete) a named semaphore </td>
	</tr>
	<tr>
		<th> Library & Syntax </th>
		<td> 

```c
<semaphore.h>

int sem_unlink(const char *name);
``` 
</td>
		</tr>
		<tr>
		<th> Example </th>
		<td>

```c
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
</td>
		</tr>
</table>

