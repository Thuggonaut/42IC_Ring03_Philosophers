#include "../inc/philo.h"

void	ph_status(t_ph_status status, t_ph *philo)
{
	long	elapsed;
	bool	end_time;

	elapsed = gettime(MILLISECONDS) - philo->data->start_time;
	if (get_bool(&philo->ph_mutex, &philo->max_meals))
		return ;
	else
	{
		handle_mutex(&philo->data->write_mutex, LOCK);
		end_time = get_bool(&philo->data->access_mutex, &philo->data->end_time);
		if ((status == TAKES_LEFTFORK || status == TAKES_RIGHTFORK) && !end_time)
			printf(WHITE"%-6ld"RESET" %d has taken a fork\n", elapsed, philo->ph_id);
		else if (status == EATING && !end_time)
			printf(WHITE"%-6ld"GREEN" %d is eating\n"RESET, elapsed, philo->ph_id);
		else if (status == SLEEPING && !end_time)
			printf(WHITE"%-6ld"RESET" %d is sleeping\n", elapsed, philo->ph_id);
		else if (status == THINKING && !end_time)
			printf(WHITE"%-6ld"RESET" %d is thinking\n", elapsed, philo->ph_id);
		else if (status == DIED)
			printf(RED"%-6ld %d died\n"RESET, elapsed, philo->ph_id);
	}
	handle_mutex(&philo->data->write_mutex, UNLOCK);
}
