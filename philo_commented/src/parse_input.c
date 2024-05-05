#include "../inc/philo.h"

//Define a function to convert the string input arguments into long integers. Static because it's only used for `parse_input()` here
static long	ft_atol(const char *s)
{
	long		res; //To store the converted string to integer. Long to handle larger than int data
	
	res = 0;
	while ((*s == '+'|| *s == 32 || (*s >= 9 && *s <= 13))) //Skip leading whitespaces
		s++;
	if (*s == '-') //Check for negative signs
		return (0); //Simply return. The error message is handled in `check_int_range()`
	if (!(*s >= '0' && *s <= '9')) //Check for invalid characters that are not digits
	{
		error_msg("Input Error: Digit values only");
		return (0);
	}
	while (*s >= '0' && *s <= '9') //Traverse the string input and convert into digits
		res = (res * 10) + (*s++ - '0');
	return (res);
}

//Define a function to check for int overflows
static long	check_int_range(t_data *data, char *argv)
{
	long	input; //To store the converted argv

	input = ft_atol(argv); //Convert argv to a long integer
	if (input > INT_MAX) //If the result is greater than INT_MAX, print error and flag the error
	{
		error_msg("Input Error: The value cannot exceed 2147483647");
		data->error_flag = 1;
	}
	if (input < 1) //If not positive, print error and flag the error
	{
		error_msg("Input Error: Positive values only");
		data->error_flag = 1;
	}
	return (input); //If valid, return the converted argv
}

//Should not test when either `time_to_die`, `time_to_eat` or `time_to_sleep` is under 60`ms`
//Define a function to parse the input and convert the strings to their required integer values
void	parse_input(t_data *data, char **argv)
{
	data->ph_total = check_int_range(data, argv[1]); //Convert total number of philos to a long integer
	if (data->ph_total > PH_MAX || data->ph_total < 1) //Check against evaluation requirements: should not test with more than 200 philos
	{
		error_msg("Input Error: Total number of philos must be 1 - 200");
		data->error_flag = 1;
	}
	data->time_to_die = check_int_range(data, argv[2]) * 1000; //Convert assigned values to milliseconds (* 1000)
	data->time_to_eat = check_int_range(data, argv[3]) * 1000;
	data->time_to_sleep = check_int_range(data, argv[4]) * 1000;
	//Check against evaluation requirements: should not test when these values are under 60ms
	if (data->time_to_die < 60000 || data->time_to_sleep < 60000 || data->time_to_eat < 60000)
	{
		error_msg("Input Error: Each of the 'time_to' values must exceed 60");
		data->error_flag = 1;
	}
	if (argv[5]) //Check if there is the optional input of number of meals all philos must eat
		data->meals_total = check_int_range(data, argv[5]);
	else //Indicate this value has not been initialized with a `-1`
		data->meals_total = -1;
}