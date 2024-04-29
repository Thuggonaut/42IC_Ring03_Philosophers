#include "philo.h"

//Define a function to check the values returned from mutex operations, and exit upon error
static void	mutex_error_check(int status, t_ftcode ftcode)
{
	if (status != 0)
	{
		error_exit("Mutex error");
		return ;
	}
}

//Define a function to check the values returned from thread functions, and exit upon error
static void	thread_error_check(int status, t_ftcode ftcode)
{
	if (status != 0)
	{
		error_exit("Thread error");
		return ;
	}
}

//Define a wrap around function that handles the mutex operations for simplification and readability
void	handle_mutex(t_mtx *mtx, t_ftcode ftcode)
{
	if (ftcode == LOCK)
		mutex_error_check(pthread_mutex_lock(mtx), ftcode);
	else if (ftcode == UNLOCK)
		mutex_error_check(pthread_mutex_unlock(mtx), ftcode);
	else if (ftcode == INIT)
		mutex_error_check(pthread_mutex_init(mtx, NULL), ftcode);
	else if (ftcode == DESTROY)
		mutex_error_check(pthread_mutex_destroy(mtx), ftcode);
	else
	{
		error_exit("ftcode options: LOCK, UNLOCK, INIT, DESTROY");
		return ;
	}
} 

//Define a wrap around function that handles the thread functions for simplification and readability
void	handle_thread(pthread_t *thread_info, void *(*foo)(void *),
		void *t_data, t_ftcode ftcode)
{
	if (ftcode == CREATE)
		thread_error_check(pthread_create(thread_info, NULL, foo, t_data), ftcode);
	else if (ftcode == JOIN)
		thread_error_check(pthread_join(*thread_info, NULL), ftcode);
	else if (ftcode == DETACH)
		thread_error_check(pthread_detach(*thread_info), ftcode);
	else
	{
		error_exit("ftcode options: CREATE, JOIN, DETACH");
		return ;
	}
}

//Define a function to safely set boolean variables and avoid writing repetative lock/unlock of mutexes
void	set_bool(t_mtx	*mutex, bool *dst, bool value)
{
	handle_mutex(mutex, LOCK); //Lock mutex to prevent other threads from accessing
	*dst = value; //Modify the boolean value before unlocking the mutex
	handle_mutex(mutex, UNLOCK); //Release for other threads access, ensuring only one thread can modify the variable at a time
}

//Define a function to safely retrieve the value of a boolean
bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	retrieved; //To store retrieved boolean value

	handle_mutex(mutex, LOCK); //Lock mutex to prevent other threads from accessing
	retrieved = *value; //Access the boolean value and assign to local variable before unlocking the mutex
	handle_mutex(mutex, UNLOCK); //Release for other threads access
	return (retrieved); 
}

//Define a function to safely set the value of a long integer variable from the data structs
void	set_long(t_mtx *mutex, long *dst, long value)
{
	handle_mutex(mutex, LOCK);
	*dst = value;
	handle_mutex(mutex, UNLOCK);
}

//Define a function to safely retrieve the value of a long integer variable 
long	get_long(t_mtx *mutex, long *value)
{
	long	retrieve;

	handle_mutex(mutex, LOCK);
	retrieve = *value;
	handle_mutex(mutex, UNLOCK);
	return (retrieve);
}
