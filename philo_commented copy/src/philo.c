#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data	data; //Declare a data struct for the philo simulation

	if (argc == 5 || argc == 6) //Check for correct number of input arguments, if so, execute the following
	{
		data.error_flag = 0; //Initialize to 0
		parse_input(&data, argv); //Parse the input and convert the strings to their required integer values
		if (!data.error_flag) //If no errors, execute the following
		{
			data_init(&data); //Initialise the data, philo and forks arrays for simulation
			sim_start(&data); //Start the simulation, where the philos eat, think, sleep
			free_things(&data); //Free up memory and clean before termination
		}
		else //If errors, exit
			return (1);
	}
	else //If the number of input is incorrect, print options and exit
		error_exit("Input Error\n" YELLOW "Please enter: ./philo <no. of philos> <time_to_die> "
			"<time_to_eat> <time_to_sleep> <max_meals> (optional)\n"
			"For example: ./philo 5 800 200 200 7" RESET);
	return (0);
}
