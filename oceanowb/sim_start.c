#include "philo.h"

//Define a function where the current thread/philo eats, sleeps, thinks
static void	*dining_philos(void *ph_data)
{
	t_ph	*philo; //A pointer variable for each philo struct 

	philo = (t_ph *)ph_data; //`ph_data` will represent `&data->philos_arr[i]`. In other words, philo will be the `i`th philo
	wait_all_threads(philo->data); //Wait for `threads_ready` to become true before all philos can execute concurrently (start simulation)
	//set_long(&philo->ph_mutex, &philo->meal_time, gettime(MILLISECONDS));
	//increase_long(&philo->data->access_mutex, &philo->data->threads_running_nbr); //TODO
	//de_synchronize_philos(philo); //TODO
	while (!get_bool(&philo->data->access_mutex, &philo->data->end_time)) //Loop until `end_time` is true
	{
		if (get_bool(&philo->ph_mutex, &philo->max_meals)) //If `max_meals` is true, break out of loop
			break ;
		eating(philo); //TODO
		write_status(SLEEPING, philo); //Print `philo is sleeping`
		ft_usleep(philo->data->time_to_sleep, philo->data); //Introduce a sleep duration for the current philo between eating and thinking. See #1
		thinking(philo, false); //TODO
	}
	return (NULL);
}

//Define a function to start the simulation following data initialization
void	sim_start(t_data *data)
{
	int	i;

	i = 0;
	if (data->meals_total == 0) //If the optional argument is `0`, return to main()
		return ;
	/*else if (data->ph_total == 1) //Handle a single philo //TODO
		handle_thread(&data->philos_arr[0].ph_thread, lone_philo,
			&data->philos_arr[0], CREATE);*/
	else //If there are more than 1 philos, create each of their threads
		while (i < data->ph_total) //dining_philos() is passed for each philo to execute concurrently (when `threads_ready` = true)
		{
			handle_thread(&data->philos_arr[i].ph_thread, dining_philos, &data->philos_arr[i], CREATE);
			i++;
		}
	//handle_thread(&data->monitor, monitor_dinner, data, CREATE); 
	data->start_time = gettime(MILLISECONDS); //Record the start time of the simulation in milliseconds as required
	set_bool(&data->access_mutex, &data->threads_ready, true); //Set to true to indicate all the threads are ready to start
	//Simulation starts here
	i = 0;
	while (i < data->ph_total) //For each philo
		handle_thread(&data->philos_arr[i++].ph_thread, NULL, NULL, JOIN); //Wait (join()) for the current philo/thread to finish its execution, e.g. complete their max_meals
	set_bool(&data->access_mutex, &data->end_time, true); //TODO comment
	handle_thread(&data->monitor, NULL, NULL, JOIN);
}

/*
NOTES:

#1
A sleep duration between actions simulates the time spent by philos sleeping after eating and before thinking.
	- This sleep time is essential for simulating realistic behavior.
	- It ensures the simulation doesn't execute actions instantaneously.
*/