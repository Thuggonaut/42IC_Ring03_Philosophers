#include "philo.h"

/*
//TODO
void	*lone_philo(void *arg)
{
	t_ph	*philo;

	philo = (t_ph *)arg;
	wait_all_threads(philo->data);
	set_long(&philo->ph_mutex, &philo->meal_time, gettime(MILLISECONDS));
	increase_long(&philo->data->access_mutex,
		&philo->data->threads_running_nbr);
	ph_status(TAKES_LEFTFORK, philo);
	while (!simulation_finished(philo->data)) //TODO
		ft_usleep(200, philo->data);
	return (NULL);
}
*/

//Define a function that checks if a philo has died based on the time elapsed since their last meal
static bool	philo_died(t_ph *philo)
{
	long	elapsed;
	long	dying_time;

	if (get_bool(&philo->ph_mutex, &philo->max_meals)) //Check if a philo has reached their maximum meals
		return (false); //Implies a philo is full and hasn't died
	elapsed = gettime(MILLISECONDS) - get_long(&philo->ph_mutex, &philo->meal_time); //Calculate the elapsed time since last meal
	dying_time = philo->data->time_to_die / 1000; //Convert `time_to_die` to milliseconds as required by rule
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
