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

//TODO
static bool	philo_died(t_ph *philo)
{
	long	elapsed;
	long	dying_time;

	if (get_bool(&philo->ph_mutex, &philo->max_meals))
		return (false);
	elapsed = gettime(MILLISECONDS) - get_long(&philo->ph_mutex,
			&philo->meal_time);
	dying_time = philo->data->time_to_die / 1000;
	if (elapsed > dying_time)
		return (true);
	return (false);
}

//TODO
void	*monitor_dinner(void *ph_data)
{
	int			i;
	t_data		*data;

	data = (t_data *)ph_data;
	while (!all_threads_running(&data->access_mutex,
			&data->threads_running_nbr, data->ph_total))
		;
	while (!get_bool(&data->access_mutex, &data->end_time))
	{	
		i = 0;
		while (i < data->ph_total && !get_bool(&data->access_mutex, &data->end_time))
		{
			if (philo_died(data->philos_arr + i))
			{
				set_bool(&data->access_mutex, &data->end_time, true);
				write_status(DIED, data->philos_arr + i);
			}
			i++;
		}
	}
	return (NULL);
}
