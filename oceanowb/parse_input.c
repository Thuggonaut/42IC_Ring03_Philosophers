#include "philo.h"

//Define a function to convert the string input arguments into long integers. Static because it's only used for `parse_input()` here
static long	ft_atol(const char *s)
{
	long		res; //To store the converted string to integer. Long to handle larger than int data
	int			len; //To check the string length is not > 10, as INT_MAX has 10 digits
	
	res = 0;
	while ((*s == 32 || *s >= 9 && *s <= 13)) //Skip leading whitespaces
		s++;
	if (*s == '-' || *s == '+') //Check for `-` signs, and skip `+` signs
	{
		if (*s == '-')
			error_exit("Positive values only");
		s++;
	}
	if (!(*s >= '0' && *s <= '9')) //Check for invalid characters that are not digits
		error_exit("Digit values only");
	len = 0;
	while (*s >= '0' && *s <= '9') //Traverse the string input and convert into digits
	{
		res = (res * 10) + (*s - '0');
		s++;
		len++;
	}
	if (len > 10 || res > INT_MAX) //Check if the input is 10 or more digits, and if the result is > INT_MAX
		error_exit("The value cannot exceed the INT_MAX value 2147483647");
	return (res);
}


//Should not test when either `time_to_die`, `time_to_eat` or `time_to_sleep` is under 60`ms`
//Define a function to parse the input and convert the strings to their required integer values
void	parse_input(t_data *data, char **argv)
{
	data->ph_total = ft_atol(argv[1]); //Convert total number of philos to a long integer
	if (data->ph_total > PH_MAX) //Check against evaluation requirements: should not test with more than 200 philos
		error_exit("Total number of philos cannot exceed 200");
	data->time_to_die = ft_atol(argv[2]) * 1000; //Convert assigned values to milliseconds (* 1000)
	data->time_to_eat = ft_atol(argv[3]) * 1000; 
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	//Check against evaluation requirements: should not test when these values are under 60ms
	if (data->time_to_die < 60000 
		|| data->time_to_sleep < 60000
		|| data->time_to_eat < 60000)
		error_exit("Each of the 'time_to' values must exceed 60");
	if (argv[5]) //Check if there is the optional input of number of meals all philos must eat
		data->meals_total = ft_atol(argv[5]);
	else //Indicate this value has not been initialized with a `-1`
		data->meals_total = -1;
}