#include "../inc/philo.h"

void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->access_mutex, &data->threads_ready))
		;
}
 
void	active_thread_counter(t_mtx *mutex, long *value)
{	
	handle_mutex(mutex, LOCK);
	(*value)++;
	handle_mutex(mutex, UNLOCK);
}

static bool	philo_died(t_ph *philo)
{
	long	elapsed;
	long	dying_time;

	if (get_bool(&philo->ph_mutex, &philo->max_meals))
		return (false);
	elapsed = gettime(MILLISECONDS) - get_long(&philo->ph_mutex, &philo->meal_time);
	dying_time = philo->data->time_to_die / 1000;
	if (elapsed > dying_time)
		return (true);
	return (false);
}

static bool	all_philos_active(t_mtx *mutex, long *threads, long ph_total)
{
	bool	value;

	value = false;
	handle_mutex(mutex, LOCK);
	if (*threads == ph_total)
		value = true;
	handle_mutex(mutex, UNLOCK);
	return (value);
}

void	*death_affirm(void *ph_data)
{
	int		i;
	t_data	*data;

	data = (t_data *)ph_data;
	while (!all_philos_active(&data->access_mutex, &data->active_philos_count, data->ph_total))
		;
	while (!get_bool(&data->access_mutex, &data->end_time))
	{
		i = 0;
		while (i < data->ph_total && !get_bool(&data->access_mutex, &data->end_time))
		{
			if (philo_died(data->philos_arr + i))
			{
				set_bool(&data->access_mutex, &data->end_time, true);
				ph_status(DIED, data->philos_arr + i);
			}
			i++;
		}
	}
	return (NULL);
}
