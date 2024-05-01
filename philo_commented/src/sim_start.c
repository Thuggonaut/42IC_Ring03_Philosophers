#include "../inc/philo.h"

//Define a function to simulate every odd numbered philo in thought. Thinking time = contention time
//Ensures an odd philo doesn't immediately aquire forks after eating, reducing contention for resources with even neighbours
//Helps synchronization with even numbered philos
static void	thinking(t_ph *philo, bool pre_simulation)
{
	long	eating_time; //To store durations of actions
	long	sleeping_time;
	long	thinking_time;

	if (!pre_simulation) //If the simulation has started
		ph_status(THINKING, philo); //Print the current philo's status as thinking
	if (philo->data->ph_total % 2 == 0) //If the total number of philos is even
		return ; //Exit this function as evens are already eating
	eating_time = philo->data->time_to_eat; //Assign the input value
	sleeping_time = philo->data->time_to_sleep; //Assign the input value
	thinking_time = (eating_time * 2) - sleeping_time; //Calculated as twice the eating time minus the sleeping time. See #1
	if (thinking_time < 0) //If the eating time is greater than the sleeping time, the thinking_time will be negative
		thinking_time = 0; //Prevent negative values. `0` to represent the minimum thinking time for effiency
	ft_usleep(thinking_time * 0.3, philo->data); //The thinking_time multiplier is arbitrary, the higher the slower execution of the simulation
}

//Define a function that synchronizes the philos dining, so they don't all attempt forks at the same time, leading to deadlocks
static void	synchronize_dining(t_ph *philo)
{
	if (philo->ph_id % 2 == 0)
		ft_usleep(30000, philo->data); //If philo even, introduce a delay of 30 seconds to synchronise with odd philos. See #2
	else //If philo odd
		thinking(philo, true); //Initialize the philo as immediately thinking. Set the bool pre_simulation to `true` because we're in the initialization phase
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

//Define a function where the current thread/philo eats, sleeps, thinks
static void	*dining_philos(void *ph_data)
{
	t_ph	*philo; //A pointer variable for each philo struct 

	philo = (t_ph *)ph_data; //`ph_data` will represent `&data->philos_arr[i]`. In other words, philo will be the `i`th philo
	wait_all_threads(philo->data); //Wait for `threads_ready` to become true before all philos can execute concurrently (start simulation)
	set_long(&philo->ph_mutex, &philo->meal_time, gettime(MILLISECONDS)); //Track the time of the dining process
	active_thread_counter(&philo->data->access_mutex, &philo->data->active_philos_count); //Increment the `active_philos_count` value by 1
	synchronize_dining(philo); //Initialize synchronization of each philo to avoid deadlocks and resource contention
	while (!get_bool(&philo->data->access_mutex, &philo->data->end_time)) //Loop until `end_time` is true
	{
		if (get_bool(&philo->ph_mutex, &philo->max_meals)) //If `max_meals` is true, break out of loop
			break ;
		eating(philo); //Simulate a philo eating
		ph_status(SLEEPING, philo); //Print `philo is sleeping`
		ft_usleep(philo->data->time_to_sleep, philo->data); //Introduce a sleep duration for the current philo between eating and thinking. See #3
		thinking(philo, false); //Simulate a philo thinking. Set the bool pre_simulation to `false` because we're now in the simulation phase
	}
	return (NULL);
}

//Define a function to start the simulation following data initialization
void	sim_start(t_data *data)
{
	int	i; //Loop counter

	i = 0;
	if (data->meals_total == 0) //If the optional argument is `0`, return to main()
		return ;
	else if (data->ph_total == 1) //check if the input number of philos is 1
		handle_thread(&data->philos_arr[0].ph_thread, single_philo, &data->philos_arr[0], CREATE); //Create a thread for the single philo
	else //If there are more than 1 philos, create each of their threads
	{
		while (i < data->ph_total) //dining_philos() is passed for each philo to execute concurrently (when `threads_ready` = true)
		{
			handle_thread(&data->philos_arr[i].ph_thread, dining_philos, &data->philos_arr[i], CREATE);
			i++;
		}
	}
	handle_thread(&data->death_check, death_affirm, data, CREATE); //Create one seperate thread for the death_affirm() that checks for deaths
	data->start_time = gettime(MILLISECONDS); //Record the start time of the simulation in milliseconds as required
	set_bool(&data->access_mutex, &data->threads_ready, true); //Set to true to indicate all the threads are ready to start
	//Simulation starts here
	i = 0;
	while (i < data->ph_total) //For each philo
		handle_thread(&data->philos_arr[i++].ph_thread, NULL, NULL, JOIN); //Wait (join()) for the current philo/thread to finish its execution, e.g. complete their max_meals
	set_bool(&data->access_mutex, &data->end_time, true); //Update `end_time` to true since all the philos have completed their meals
	handle_thread(&data->death_check, NULL, NULL, JOIN); //Wait for the death_check thread ti finish executing `death_affirm()`
}

/*
NOTES:

#1
The reason for this calculation is to ensure that the philosopher does not immediately acquire forks after eating, reducing contention for resources.

#2
The philosopher will not immediately acquire forks after eating, reducing contention for resources.
	- 30 seconds is arbitrary. 
	- The higher the value, the slower the execution of the simulation e.g. longer wait period before proceeding with their actions.
	- The lower the value, the faster the execution of the simulation e.g. shorter wait, but risks deadlocks or starvation.

#3
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
