#include "../inc/philo.h"

/*
5️⃣ About the logs of your program:
1. 🔸 Any state change of a philosopher must be formatted as follows:
- `timestamp_in_ms` X has taken a fork
- `timestamp_in_ms` X is eating
- `timestamp_in_ms` X is sleeping
- `timestamp_in_ms` X is thinking
- `timestamp_in_ms` X died
2. 🔸 Replace `timestamp_in_ms` with the current timestamp in milliseconds and `X` with the philosopher number.
3. 🔸 A displayed state message should not be mixed up with another message.
4. 🔸 A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
*/

//Define a function to print the logs of the simulation
void	ph_status(t_ph_status status, t_ph *philo)
{
	long	elapsed; //To store the elapsed time since the start of the simulation
	bool	end_time; //To store the value of whether the simulation has ended, true/false

	elapsed = gettime(MILLISECONDS) - philo->data->start_time; //Calculate the elapsed time by subtracting `start_time` of the simulation from the current time
	if (get_bool(&philo->ph_mutex, &philo->max_meals)) //Check if the philo has reached its max allowed meals. First lock the mutex before accessing the bool value
		return ; //If so, return to avoid more eating etc
	else //Print the log based on the status of the philo and if the simulation has not ended
	{
		handle_mutex(&philo->data->write_mutex, LOCK); //Lock before printing to ensure thread safety
		end_time = get_bool(&philo->data->access_mutex, &philo->data->end_time); //Retrieve the value of `end_time`
		if ((status == TAKES_LEFTFORK || status == TAKES_RIGHTFORK) && !end_time)
			printf(WHITE"%-6ld"RESET" %d has taken a fork\n", elapsed, philo->ph_id); //See note #1 for `%-61d`
		else if (status == EATING && !end_time)
			printf(WHITE"%-6ld"GREEN" %d is eating\n"RESET, elapsed, philo->ph_id);
		else if (status == SLEEPING && !end_time)
			printf(WHITE"%-6ld"RESET" %d is sleeping\n", elapsed, philo->ph_id);
		else if (status == THINKING && !end_time)
			printf(WHITE"%-6ld"RESET" %d is thinking\n", elapsed, philo->ph_id);
		else if (status == DIED)
			printf(RED"%-6ld %d died\n"RESET, elapsed, philo->ph_id);
	}
	handle_mutex(&philo->data->write_mutex, UNLOCK); //Unlock for the next thread to access
}

/*
NOTES:

#1	
`%ld` is a format specifier used for printing a long integer.
	- `-6` is a width specifier that ensures the printed number occupies at least 6 characters, left-aligning the output. 
	- If the number is less than 6 characters, spaces will be added to the right to meet the width requirement.
	- Makes the output easier to read when aligned.
*/