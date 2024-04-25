#include "philo.h"

//Define a function to simulate a philo in thought, but also:
//Ensures a philo doesn't immediately aquire forks after eating, reducing contention for resources
//Helps synchronization
static void	thinking(t_ph *philo, bool pre_simulation)
{
	long	eating_time; //To store durations
	long	sleeping_time;
	long	thinking_time;

	if (!pre_simulation)
		ph_status(THINKING, philo);
	if (philo->data->ph_total % 2 == 0)
		return ;
	eating_time = philo->data->time_to_eat;
	sleeping_time = philo->data->time_to_sleep;
	thinking_time = (eating_time * 2) - sleeping_time;
	if (thinking_time < 0)
		thinking_time = 0;
	ft_usleep(thinking_time * 0.5, philo->data); //TODO: thinking_time multiplier is arbitrary, the higher the slower execution of the simulation
}

//Define a function that simulates a philos's eating
static void	eating(t_ph *philo)
{
	handle_mutex(&philo->left_fork->fork_mutex, LOCK); //Lock the assigned fork to ensure mutual exclusion
	ph_status(TAKES_LEFTFORK, philo); //Print the status
	handle_mutex(&philo->right_fork->fork_mutex, LOCK); ////Lock the assigned fork to ensure mutual exclusion
	ph_status(TAKES_RIGHTFORK, philo); //Print the status
	set_long(&philo->ph_mutex, &philo->meal_time, gettime(MILLISECONDS)); //Update the meal time with the current time, for this current meal
	philo->meal_count++; //Increment to indicate the philo have eaten a/another meal
	ph_status(EATING, philo); //Print the status
	ft_usleep(philo->data->time_to_eat, philo->data); //Introduce a delay to simulate the `time_to_eat` the philo spends eating
	if (philo->data->meals_total > 0 && philo->meal_count == philo->data->meals_total) //Check if the philo has reached its `max_meals`
		set_bool(&philo->ph_mutex, &philo->max_meals, true); //If so, set the bool to `true`
	handle_mutex(&philo->left_fork->fork_mutex, UNLOCK); //Release the forks for the next philo
	handle_mutex(&philo->right_fork->fork_mutex, UNLOCK);
}

//TODO and change ft name
static void	de_synchronize_philos(t_ph *philo)
{
	if (philo->data->ph_total % 2 == 0)
	{
		if (philo->ph_id % 2 == 0)
			ft_usleep(30000, philo->data); //TODO why 30000
	}
	else
	{
		if (philo->ph_id % 2)
			thinking(philo, true); //TODO why true
	}
}	

//Define a function where the current thread/philo eats, sleeps, thinks
static void	*dining_philos(void *ph_data)
{
	t_ph	*philo; //A pointer variable for each philo struct 

	philo = (t_ph *)ph_data; //`ph_data` will represent `&data->philos_arr[i]`. In other words, philo will be the `i`th philo
	wait_all_threads(philo->data); //Wait for `threads_ready` to become true before all philos can execute concurrently (start simulation)
	set_long(&philo->ph_mutex, &philo->meal_time, gettime(MILLISECONDS)); //Track the time of the dining process
	active_thread_counter(&philo->data->access_mutex, &philo->data->active_philos_count); //Increment the `active_philos_count` value by 1
	//de_synchronize_philos(philo); //TODO and update name
	while (!get_bool(&philo->data->access_mutex, &philo->data->end_time)) //Loop until `end_time` is true
	{
		if (get_bool(&philo->ph_mutex, &philo->max_meals)) //If `max_meals` is true, break out of loop
			break ;
		eating(philo); //Simulate a philo eating
		ph_status(SLEEPING, philo); //Print `philo is sleeping`
		ft_usleep(philo->data->time_to_sleep, philo->data); //Introduce a sleep duration for the current philo between eating and thinking. See #1
		thinking(philo, false); //Simulate a philo thinking TODO why false
	}
	return (NULL);
}

//Define a function to start the simulation following data initialization
void	sim_start(t_data *data)
{
	int	i;

	i = 0;
	if (data->meals_total == 0) //If the optional argument is `0`, return to main()
		return ;
	else if (data->ph_total == 1) //check if the input number of philos is 1
		handle_thread(&data->philos_arr[0].ph_thread, single_philo, &data->philos_arr[0], CREATE); //Create a thread for the single philo
	else //If there are more than 1 philos, create each of their threads
		while (i < data->ph_total) //dining_philos() is passed for each philo to execute concurrently (when `threads_ready` = true)
		{
			handle_thread(&data->philos_arr[i].ph_thread, dining_philos, &data->philos_arr[i], CREATE);
			i++;
		}
	handle_thread(&data->death_check, death_affirm, data, CREATE); //Create one seperate thread for the death_affirm() that checks for deaths
	data->start_time = gettime(MILLISECONDS); //Record the start time of the simulation in milliseconds as required
	set_bool(&data->access_mutex, &data->threads_ready, true); //Set to true to indicate all the threads are ready to start
	//Simulation starts here
	i = 0;
	while (i < data->ph_total) //For each philo
		handle_thread(&data->philos_arr[i++].ph_thread, NULL, NULL, JOIN); //Wait (join()) for the current philo/thread to finish its execution, e.g. complete their max_meals
	set_bool(&data->access_mutex, &data->end_time, true); //TODO comment
	handle_thread(&data->death_check, NULL, NULL, JOIN); //Wait for the death_check thread ti finish executing `death_affirm()`
}

/*
NOTES:

#1
A sleep duration between actions simulates the time spent by philos sleeping after eating and before thinking.
	- This sleep time is essential for simulating realistic behavior.
	- It ensures the simulation doesn't execute actions instantaneously.
	- `philo->data->time_to_sleep` complies with the project rules. 

A sleep duration prevents data races:
	- In a multithreaded environment, where multiple philos (threads) are accessing shared data (like data->end_time), 
	  it's crucial to prevent data races. 
	- Data races occur when multiple threads access shared data concurrently, and at least one of the accesses is a write
	  operation. 
	- By using ft_usleep, it allows other threads to have a chance to access shared data without contention.
	- In other words, the thread voluntarily relinquishes the CPU time for a specified period, allowing the operating system 
	  scheduler to switch to other threads that are ready to execute.
	  	- In a multithreaded program, threads often compete for CPU time. 
		- Even if a thread is blocked waiting for a mutex lock, it still consumes CPU resources while in that waiting state. 
		- This consumption can be significant if the thread is continuously checking a condition or waiting for some event.
*/