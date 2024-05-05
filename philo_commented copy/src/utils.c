#include "../inc/philo.h"

//Print custom error message and return to function
void	error_msg(const char *error_msg)
{
	printf(MAGENTA "%s\n" RESET, error_msg);
}


//Define malloc with a NULL return check for re-use and readability
//It returns a pointer to the allocated memory on success and NULL on failure
void	*ft_malloc(size_t bytes)
{
	void	*retrieve;

	retrieve = malloc(bytes);
	if (retrieve == NULL)
	{
		error_msg("Memory allocation unsuccessful");
		return (NULL);
	}
	return (retrieve);
}

//Define a function that retrieves the current system time and returns it in converted units
//Time elapsed from January 1, 1970
//`time_t		tv_sec;`	//whole seconds, the integral part of the current time
//`suseconds_t	tv_usec;`	//microseconds, the fractional part of the current time
long	gettime(t_time_unit time_unit)
{
	struct timeval current_time; //Struct to hold the current time
		
	if (gettimeofday(&current_time, NULL) != 0) //Get the current system time
	{
		error_msg("Error: gettimeofday failed"); //Exit with error message is a non-zero integer is returned
		return (1);
	}
	//Calculate the time in the specified unit
	if (time_unit == MILLISECONDS) //Convert seconds to miliseconds, do the same for microseconds, then add the two for the total
		return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	else if (time_unit == MICROSECONDS) //Convert seconds to microseconds, add it to the `tv_usec` microseconds to get total microseconds
		return (current_time.tv_sec * 1000000 + current_time.tv_usec);
	else if (time_unit == SECONDS) //Add the `tv_sec` seconds to the converted microseconds to seconds for a total of seconds
		return (current_time.tv_sec + current_time.tv_usec / 1000000);
	else
	{
		error_msg("Invalid time unit specified");
		return (1);
	}
	return (-1); //The compiler needs a return statement but it will never be reached, as `error_exit` will texit the code block
}

//Define own usleep() function to more accurately delay execution (sleep duration)
//Default usleep() otherwise can vary depending on the operating system
void	ft_usleep(long sleep_time, t_data *data)
{
	long	start; //To store the current time when the function starts executing
	long	elapsed; //To store the elapsed time since the execution start
	long	remaining; //To store the remaining time to sleep

	start = gettime(MICROSECONDS); //Retrieve the start time, from which the elapsed is measured
	while (gettime(MICROSECONDS) - start < sleep_time) //Loop until elapsed time is >= than time to sleep, ensuring a waiting state
	{
		if (get_bool(&data->access_mutex, &data->end_time)) //If the simulation ended, there's no need to continue waiting
			break ; //Exit function
		elapsed = gettime(MICROSECONDS) - start;
		remaining = sleep_time - elapsed; //Calculate the remaining time to sleep
		if (remaining > 10000) //If remaining time is more than 10 milliseconds
			usleep(remaining / 2); //Sleep for half of the remaining time. See #1
		else //If remaining time is less than 10 milliseconds
			while (gettime(MICROSECONDS) - start < sleep_time) //Continuously wait until the sleep time is reached
				;
	}
}

//Defina a function to free up memory and clean before termination
void	free_things(t_data *data)
{
	t_ph	*philo; //Access the philo's data elements
	int		i; //Loop counter

	i = 0;
	while (i < data->ph_total) //Loop through each philo in the array
	{
		philo = data->philos_arr + i;
		handle_mutex(&philo->ph_mutex, DESTROY); //Destroy the mutex associated with the philo
		i++;
	}
	handle_mutex(&data->write_mutex, DESTROY); //Destroy the mutex associated with writing operations
	handle_mutex(&data->access_mutex, DESTROY); ////Destroy the mutex associated with controlling access to variables
	free(data->forks_arr); //Deallocate the memory for the forks and philos array preventing memory leaks
	free(data->philos_arr);
}

/*
NOTES:

#1
Sleeping for half the remaining time reduces the chances of overshooting the desired sleep duration. 
	- This ensures the program wakes up to resume execution closer to the intended time (halfway through the remaining time).
*/