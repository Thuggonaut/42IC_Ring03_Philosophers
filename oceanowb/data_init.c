#include "philo.h"

//Define a function to initialize the data structs needed for simulation, taking a pointer to the t_data struct
void	data_init(t_data *data)
{
	int		i; //To track the loop count

	i = 0;
	data->end_time = false; //Ensure that the simulation starts in an active state (simulation has not ended)
	//data->all_threads_ready = false;
	//data->threads_running_nbr = 0;
	data->philos_arr = ft_malloc(data->ph_total * sizeof(t_ph));
	data->forks_arr = ft_malloc(data->ph_total * sizeof(t_fork));
	//safe_mutex_handle(&data->write_mutex, INIT);
	//safe_mutex_handle(&data->data_mutex, INIT);
	while (i < data->ph_total)
	{
		safe_mutex_handle(&data->forks_arr[i].fork, INIT);
		data->forks_arr[i].fork_id = i;
		i++;
	}
	philo_init(data);
}