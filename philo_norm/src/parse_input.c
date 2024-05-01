/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 23:16:45 by tquemato          #+#    #+#             */
/*   Updated: 2024/05/01 16:44:20 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	whitespace(char c)
{
	return (c == '+' || (c >= 9 && c <= 13) || 32 == c);
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	input_error(int code)
{
	if (code == 1)
	{
		error_exit("Input Error: Positive values only");
		return (1);
	}
	if (code == 2)
	{
		error_exit("Input Error: Digit values only");
		return (1);
	}
	if (code == 3)
	{
		error_exit("Input Error: The value cannot exceed 2147483647");
		return (1);
	}
	return (0);
}

static long	ft_atol(const char *s)
{
	int		len;
	long	res;

	while (whitespace(*s))
		++s;
	if (*s == '-')
		input_error(1);
	if (!is_digit(*s))
		input_error(2);
	len = 0;
	res = 0;
	while (is_digit(*s))
	{
		res = (res * 10) + (*s++ - '0');
		len++;
	}
	if (len > 10 || res > INT_MAX)
		input_error(3);
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
	if (data->time_to_die < 60000 || data->time_to_sleep < 60000
		|| data->time_to_eat < 60000)
	{
		error_exit("Input Error: Each of the 'time_to' values must exceed 60");
		return ;
	}
	if (argv[5])
		data->meals_total = ft_atol(argv[5]);
	else
		data->meals_total = -1;
}
