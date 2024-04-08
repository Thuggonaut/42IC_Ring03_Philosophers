#include "philo.h"

//Define a function where the threads/philos eats, sleeps, thinks
static void	*dining_philos(void *data)
{
	t_ph	*philo; //A pointer variable for each philo struct 

	philo = (t_ph *)data;
	wait_all_threads(philo->data); //TODO comment
	set_long(&philo->ph_mutex, &philo->meal_time,
		gettime(MILLISECONDS));
	increase_long(&philo->data->bool_access_mutex,
		&philo->data->threads_running_nbr);
	de_synchronize_philos(philo);
	while (!simulation_finished(philo->data))
	{
		if (get_bool(&philo->ph_mutex, &philo->max_meals))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo, false);
	}
	return (NULL);
}

//Define a function to start the simulation following data initialization
void	sim_start(t_data *data)
{
	int			i;

	i = 0;
	if (data->meals_total == 0) //If the optional argument is `0`, return to main()
		return ;
	/*else if (data->ph_total == 1) //Handle a single philo //TODO
		safe_thread_handle(&data->philos_arr[0].ph_thread, lone_philo,
			&data->philos_arr[0], CREATE);*/
	else //If there are more than 1 philos, create each of their threads
		while (i++ < data->ph_total)
			handle_thread(&data->philos_arr[i].ph_thread, dining_philos,
				&data->philos_arr[i], CREATE);
	handle_thread(&data->monitor, monitor_dinner, data, CREATE); 
	data->start_time = gettime(MILLISECONDS);
	set_bool(&data->bool_access_mutex, &data->threads_ready, true); //TODO comment: set to true after all the threads are ready to start
	i = 0;
	while (i++ < data->ph_total)
		handle_thread(&data->philos_arr[i].ph_thread, NULL, NULL, JOIN);
	set_bool(&data->bool_access_mutex, &data->end_time, true); //TODO comment
	handle_thread(&data->monitor, NULL, NULL, JOIN);
}