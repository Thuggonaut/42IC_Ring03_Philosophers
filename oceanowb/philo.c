#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data; //TODO comment

	if (argc == 5 || argc == 6) //Check for correct number of input arguments, if so, execute the following
	{
		parse_input(&data, argv); //Parse the input and convert the strings to their required integer values
		data_init(&data); //Initialise the data, philo and forks arrays for simulation
		sim_start(&data); //TODO
		//clean(&data); //TODO
	}
	else //The number of input is incorrect
	{
		error_exit("Input Error\n"
			YELLOW "Please enter: ./philo <no. of philos> <time_to_die> "
			"<time_to_eat> <time_to_sleep> <max_meals> (optional)\n"
			"For example: ./philo 5 800 200 200 7" RESET);
	}
}
