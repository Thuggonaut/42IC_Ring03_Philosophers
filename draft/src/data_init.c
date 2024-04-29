#include "../inc/philo.h"

//Define a function that assigns left and right forks for each philo, alternating their fork selection
//`ph_index` is `i` in `philo_innit()`
static void	assign_forks(t_ph *philo, t_fork *forks_arr, int ph_index)
{
	int	ph_total; //To store the total number of philos

	ph_total = philo->data->ph_total;
	if (philo->ph_id % 2 != 0) //If ph_id is odd
	{
		philo->left_fork = &forks_arr[(ph_index + 1) % ph_total];
		philo->right_fork = &forks_arr[ph_index];
	}
	if (philo->ph_id % 2 == 0) //If ph_id is even, right and left forks are swapped to prevent deadlocks. See #1
	{
		philo->left_fork = &forks_arr[ph_index];
		philo->right_fork = &forks_arr[(ph_index + 1) % ph_total];
	}	
}

//Defina a funtion to initialize each philo
static void	philo_init(t_data *data)
{
	int		i; //To track the loop count
	t_ph	*philo; //A pointer variable for each philo struct 

	i = 0;
	while (i < data->ph_total)  //Iterate up to ph_total times begining with [0]
	{
		philo = data->philos_arr + i; //Assign to the current philo, the address of the i'th position of the array
		philo->ph_id = i + 1; //Assign to the current philo, an ID (starting from `1`)
		philo->max_meals = false; //**************Where does this change if true************* //TODO comment
		philo->meal_count = 0; //The philo hasn't eaten yet
		handle_mutex(&philo->ph_mutex, INIT); //Initialize the philo's mutex to allow one thread (philo) to access critical sections (variables, e.g. meal_time) at a time
		philo->data = data; //TODO comment
		assign_forks(philo, data->forks_arr, i); //TODO comment
		i++; 
	}
}

//Define a function to initialize the data structs needed for simulation, taking a pointer to the t_data struct
void	data_init(t_data *data)
{
	int		i; //To track the loop count

	i = 0;
	data->end_time = false; //Ensure that the simulation starts in an active state (simulation has not ended)
	data->threads_ready = false; //Threads are yet to be initialised
	data->active_philos_count = 0; //Threads are yet to be running
	data->philos_arr = ft_malloc(data->ph_total * sizeof(t_ph)); //Allocate memory for the philos/thread array
	data->forks_arr = ft_malloc(data->ph_total * sizeof(t_fork)); //Allocate memory for the forks/mutex array
	handle_mutex(&data->write_mutex, INIT); //Initialize the mutex that controlls thread access to write to the STDOUT
	handle_mutex(&data->access_mutex, INIT); //Initialize the mutex before threads can access to bool values
	while (i < data->ph_total) //Iterate up to ph_total times, begining with [0]
	{
		handle_mutex(&data->forks_arr[i].fork_mutex, INIT); //Initialize the mutex for each fork in the fork mutex array
		data->forks_arr[i].fork_id = i; //For each fork/mutex, set the fork_id value
		i++;
	}
	philo_init(data); //TODO comment
}

/*
NOTES:

#1 
Forks assignment:

-PH_ID-	   -FORK_ARR-
Philo 1:   [1]  [0]  (left: 1, right: 0)
Philo 2:   [2]  [1]  (left: 1, right: 2)
Philo 3:   [3]  [2]  (left: 3, right: 2)
Philo 4:   [4]  [3]  (left: 3, right: 4)
Philo 5:   [0]  [4]  (left: 4, right: 0) //Wraps around to [0]

*/