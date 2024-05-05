#include "../inc/philo.h"

//Define a function to check the values returned from mutex operations, and return (and terminating) upon error
//Non-zero return values of mutex operations indicate an error
static void	mutex_error_check(int status, t_ftcode ftcode)
{
	if (status != 0 && (ftcode == LOCK || ftcode == UNLOCK 
		|| ftcode == INIT || ftcode == DESTROY))
	{
		error_exit("Mutex error");
		return ;
	}
}

//Define a function to check the values returned from thread functions, and return (and terminating) upon error
//Non-zero return values of mutex operations indicate an error
static void	thread_error_check(int status, t_ftcode ftcode)
{
	if (status != 0  && (ftcode == CREATE || ftcode == JOIN || ftcode == DETACH))
	{
		error_exit("Thread error");
		return ;
	}
}

//Define a wrap around function that handles the mutex operations for simplification and readability
//It performs the mutex operations and checks the values returned from them
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
//It performs the thread operations and checks the values returned from them
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
