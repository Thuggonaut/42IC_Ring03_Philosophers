#include "philo.h"


//Define a function for a thread to handle a singular philo
//It takes a single fork, but unable to eat
//It sleeps then returns to `sim_start()` to die
void	*single_philo(void *index)
{
	t_ph	*philo; //Pointer to the philo

	philo = (t_ph *)index; //The argument passed to `single_philo` will be the index of the philo in `philos_arr` in `handle_thread()`
	wait_all_threads(philo->data); 
	set_long(&philo->ph_mutex, &philo->meal_time, gettime(MILLISECONDS)); //Record the start time of the dining process
	active_thread_counter(&philo->data->access_mutex, &philo->data->active_philos_count); //Increment the count, to indicate this philo is now active
	ph_status(TAKES_LEFTFORK, philo); //Doesn't really, we just need the printing
	while (!get_bool(&philo->data->access_mutex, &philo->data->end_time)) //Until the end_time
		ft_usleep(200, philo->data); //philo sleeps for 200 microseconds (it waits for the second fork, but it doesnt exist)
	return (NULL);
}

//Define a function that checks if a philo has died based on the time elapsed since their last meal
static bool	philo_died(t_ph *philo)
{
	long	elapsed;
	long	dying_time;

	if (get_bool(&philo->ph_mutex, &philo->max_meals)) //Check if a philo has reached their maximum meals
		return (false); //Implies a philo is full and hasn't died
	elapsed = gettime(MILLISECONDS) - get_long(&philo->ph_mutex, &philo->meal_time); //Calculate the elapsed time since last meal
	dying_time = philo->data->time_to_die / 1000; //Convert `time_to_die` from milliseconds (from parsed) to seconds. See #1
	if (elapsed > dying_time) //If time elapsed surpasses the `time_to_die` input
		return (true); //The philo has died
	return (false); //Otherwise the philo lives
}

//Check if all the threads are running and active
static bool	all_philos_active(t_mtx *mutex, long *threads, long ph_total)
{
	bool	value; 

	value = false; //Initialize to false
	handle_mutex(mutex, LOCK); //Always lock the mutex before reading/accessing and modifying values
	if (*threads == ph_total) //If the count of threads is equal to ph_total
		value = true; //Update the bool to true
	handle_mutex(mutex, UNLOCK); //Release the mutex for the next thread
	return (value);
}

//Define a function for a seperate thread, to affirm a death, update `end_time` and print the status
void	*death_affirm(void *ph_data)
{
	int			i; //Loop counter
	t_data		*data; //Retrieve the data 

	data = (t_data *)ph_data; //Cast the ph_data pointer to a `t_data` pointer
	while (!all_philos_active(&data->access_mutex, &data->active_philos_count, data->ph_total)) //Wait until all the philos are running before further execution
		; //Once `active_philos_count` is equal to `ph_total`, continue to next line
	while (!get_bool(&data->access_mutex, &data->end_time)) //Loop until `end_time` is true, checking for deaths
	{	
		i = 0;
		while (i < data->ph_total && !get_bool(&data->access_mutex, &data->end_time)) //Iterate through each philo while the simulation is active
		{
			if (philo_died(data->philos_arr + i)) //Check if the philo has died
			{
				set_bool(&data->access_mutex, &data->end_time, true); //If so, mark the end of the simulation
				ph_status(DIED, data->philos_arr + i); //Print the death status
			}
			i++;
		}
	}
	return (NULL);
}

/*
NOTE:

#1
	- `elapsed = gettime(MILLISECONDS) - get_long(&philo->ph_mutex, &philo->meal_time);`
		- The result will be, say, 1618557858000 - 1618557855000 
		- = 3000 milliseconds

	- `dying_time = philo->data->time_to_die / 1000;`
		- time_to_die say, 2999 was converted in parsing and became 2999000
		- we need to divide it by 1000 to get it back to 2999 before comparison:
		- `if (3000 > 2999)`
*/