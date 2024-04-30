#include "../inc/philo.h"

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

