#ifndef PHILO_H
# define PHILO_H

//LIBRARIES*****
# include <stdio.h> //To call printf() for printing to the STDOUT
# include <stdlib.h> //To call malloc(), free() for memory management
# include <sys/wait.h> //To call waitpid()
# include <unistd.h> //To call write(), usleep()
# include <stdbool.h> //To use boolean values
# include <string.h> //To call memset()
# include <pthread.h> //For thread related functions
# include <sys/time.h> //To call gettimeofday()
# include <limits.h> //To use the MIN and MAX macros


//CUSTOM MACROS
# define PH_MAX 200
# define INPUT_ERROR 1
# define MALLOC_ERROR 2


//ANSI Escape Sequences for text formatting*****
# define RESET		"\033[0m" //Reset to default color 
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[1;37m"


//DATA STRUCTS*****

//Define types here to use their shortened name throughout our codes
typedef pthread_mutex_t	t_mtx; //To represent each fork

//For each fork
typedef struct s_fork
{
	t_mtx		fork_mutex; //Declare a mutex for each fork
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
	t_mtx		ph_mutex; //Mutex to allow one thread (philo) to access critical sections (variables) at a time
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
	bool			threads_ready; //TODO comment
	//long			threads_running_nbr; //TODO comment
	//pthread_t		monitor; //TODO comment
	t_fork			*forks_arr; //Pointer to the forks/mutex array
	t_ph			*philos_arr; //Pointer to the philos array
	t_mtx			access_mutex; //Controll access to bool values by multiple threads, avoiding data races
	t_mtx			write_mutex; //Control thread access, allowing one at a time to write to the STDOUT
}					t_data;


//ENUMS*****
//Enums allow you to define a set of named integer constants. Giving them symbolic names is clearer than going by numbers
//Each enumerator name represents a constant value, assigned by the compiler (unless explicitly specified), starting from 0 and incrementing by 1 for each subsequent enumerator

//For representing a philosoper's state during a simulation, and used for printing to the STDOUT
typedef enum e_status
{
	THINKING,
	TAKES_LEFTFORK,
	TAKES_RIGHTFORK,
	EATING,
	SLEEPING,
	DIED,
}			t_ph_status;

//For representing units of time for measuring durations with gettime()
typedef enum e_time_unit
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}		t_time_unit;

//For representing thread and mutex functions for cleaner readability. Used with threads_mutex.c
typedef enum e_ftcode
{
	INIT,
	CREATE,
	LOCK,
	UNLOCK,
	JOIN,
	DETACH,
	DESTROY,
}			t_ftcode;


//SIMULATION*****
void		parse_input(t_data *data, char **argv);
void		data_init(t_data *data);
void		sim_start(t_data *data);


//THREADS & MUTEXES HANDLERS*****
void		handle_mutex(t_mtx *mtx, t_ftcode ftcode);
void		handle_thread(pthread_t *thread_info, void *(*foo)(void *), void *t_data, t_ftcode ftcode);
void		wait_all_threads(t_data *data);
void		set_bool(t_mtx	*mutex, bool *dst, bool value);
bool		get_bool(t_mtx *mutex, bool *value);
void		set_long(t_mtx *mutex, long *dst, long value);
long		get_long(t_mtx *mutex, long *value);


//UTILS*****
void		*ft_malloc(size_t bytes);
void		error_exit(const char *error_msg);
long		gettime(t_time_unit time_unit);
void		ft_usleep(long sleep_time, t_data *data);
void		ph_status(t_ph_status status, t_ph *philo);

#endif