#include "../inc/philo.h"

static long	ft_atol(const char *s)
{
	long	res;
	int		len;
	
	res = 0;
	while ((*s == 32 || (*s >= 9 && *s <= 13)))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
		{
			error_exit("Input Error: Positive values only");
			return (1);
		}
		s++;
	}
	if (!(*s >= '0' && *s <= '9'))
	{
		error_exit("Input Error: Digit values only");
		return (1);
	}
	len = 0;
	while (*s >= '0' && *s <= '9')
	{
		res = (res * 10) + (*s - '0');
		s++;
		len++;
	}
	if (len > 10 || res > INT_MAX)
	{
		error_exit("Input Error: The value cannot exceed the INT_MAX value 2147483647");
		return (1);
	}
	return (res);
}

void	parse_input(t_data *data, char **argv)
{
	data->ph_total = ft_atol(argv[1]);
	if (data->ph_total > PH_MAX)
	{
		error_exit("Input Error: Total number of philos cannot exceed 200");
		return ;
	}
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (data->time_to_die < 60000 || data->time_to_sleep < 60000 || data->time_to_eat < 60000)
	{
		error_exit("Input Error: Each of the 'time_to' values must exceed 60");
		return ;
	}
	if (argv[5])
		data->meals_total = ft_atol(argv[5]);
	else
		data->meals_total = -1;
}