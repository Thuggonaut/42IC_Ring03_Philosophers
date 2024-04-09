#include "philo.h"

//Print custom error message and exit
void	error_exit(const char *error_msg)
{
	printf(MAGENTA "%s\n" RESET, error_msg);
	return (INPUT_ERROR); //Exit
}

//Define malloc with a NULL return check for re-use and readability
void	*ft_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
	{
		printf(MAGENTA "Memory allocation unsuccessful" RESET);
		return (MALLOC_ERROR); //Exit
	}
	return (ret);
}

//Define a function that implements a "busy-wait" loop to wait for all threads to become ready in a multi-threaded environment
//Since we should test with no more than 200 philos, a spin lock is appropriate. Any larger and spin locks consume CPU cycles leading to inefficiency
void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->access_mutex, &data->threads_ready)) //While `threads_ready` is false
		; //Wait until `threads_ready` becomes true
}

//Define a function that retrieves the current system time and returns it in converted units
//Time elapsed from January 1, 1970
//`time_t		tv_sec;`	//whole seconds, the integral part of the current time
//`suseconds_t	tv_usec;`	//microseconds, the fractional part of the current time
long	gettime(t_time_unit time_unit)
{
	struct timeval current_time; //Struct to hold the current time
		
	if (gettimeofday(&current_time, NULL) != 0) //Get the current system time
		error_exit("Error: gettimeofday failed"); //Exit with error message is a non-zero integer is returned
	//Calculate the time in the specified unit
	if (time_unit == MILLISECONDS) //Convert seconds to miliseconds, do the same for microseconds, then add the two for the total
		return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	else if (time_unit == MICROSECONDS) //Convert seconds to microseconds, add it to the `tv_usec` microseconds to get total microseconds
		return (current_time.tv_sec * 1000000 + current_time.tv_usec);
	else if (time_unit == SECONDS) //Add the `tv_sec` seconds to the converted microseconds to seconds for a total of seconds
		return (current_time.tv_sec + current_time.tv_usec / 1000000);
	else
		error_exit("Invalid time unit specified");
	return (-1); //The compiler needs a return statement but it will never be reached, as `error_exit` will terminate the program
}