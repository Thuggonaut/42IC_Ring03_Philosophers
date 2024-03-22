#ifndef PHILO_H
# define PHILO_H

//LIBRARIES*****
# include <stdio.h> //To call printf() for printing to the STDOUT
# include <stdlib.h> //To call malloc(), free() for memory management
//# include <stdint.h> 
//# include <sys/wait.h>
# include <unistd.h> //To call write(), usleep()
# include <stdbool.h> //To use boolean values
# include <errno.h> //To access various error codes during execution
# include <string.h> //To call memset()
# include <pthread.h> //For thread related functions
# include <sys/time.h> //To call gettimeofday()
# include <limits.h> //To use the MIN and MAX macros


//CUSTOM MACROS
# define PH_MAX 200 


//ANSI Escape Sequences for text formatting*****
# define RESET		"\033[0m" //Reset to default color 
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"


//DATA STRUCTS*****

//Define types here to use their shortened name throughout our codes
//typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx; //To represent each fork

//For each fork
typedef struct s_fork
{
	t_mtx		fork; //Declare a mutex for each fork
	int			fork_id; //Declare a variable for the fork number
}				t_fork;

//For each philosopher
typedef struct s_ph
{
	int			ph_id; //Number of each philo
	long		meal_count; //Track meals eaten
	bool		max_meals; //Flag for optional argument of meals a philo must eat
	long		meal_time; //Track the stimulation start or last meal time against the `time_to_die` argument. `long` for microseconds
	pthread_t	ph_thread; //Identifier of the thread representing the philo to manage thread operations
	t_fork		*left_fork; //Pointer to left fork in the mutex array
	t_fork		*right_fork; //Pointer to right fork in the mutex array
	//t_mtx		philo_mutex;
	t_data		*data; //Allow each philo access to the simulation data
}				t_ph;

//For managing the rules of the mandatory part
typedef struct s_data
{
	long			ph_total; //Philos in total, the first argument `number_of_philosophers`
	long			time_to_die; //Second argument
	long			time_to_eat; //Third argument
	long			time_to_sleep; //Fourth argument
	long			meals_total; //Track if there is a fifth argument `number_of_times_each_philosopher_must_eat`. If not, assign `-1` indicating it has not been set
	long			start_time; //Track when the simulation starts
	bool			end_time; //Track when the simulation ends (when a philo dies, or when all philos have eaten number of `meals_total`)
	//bool			all_threads_ready;
	//long			threads_running_nbr;
	//pthread_t		monitor;
	t_fork			*fork_arr; //Pointer to the forks/mutex array
	t_ph			*philos_arr; //Pointer to the philos array
	//t_mtx			data_mutex;
	//t_mtx			write_mutex;
}					t_data;


//PARSING*****
void		parse_input(t_data *data, char **argv);


//UTILS*****
void		error_exit(const char *error_msg);

#endif