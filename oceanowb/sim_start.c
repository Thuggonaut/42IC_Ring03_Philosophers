#include "philo.h"

//Define a function that simulates a philos's eating
static void	eat(t_ph *philo)
{
	handle_mutex(&philo->left_fork->fork_mutex, LOCK); //Lock the assigned fork to ensure mutual exclusion
	ph_status(TAKES_LEFTFORK, philo); //Print the status
	handle_mutex(&philo->right_fork->fork_mutex, LOCK); ////Lock the assigned fork to ensure mutual exclusion
	ph_status(TAKES_RIGHTFORK, philo); //Print the status
	set_long(&philo->ph_mutex, &philo->meal_time, gettime(MILLISECONDS)); //Update the meal time with the current time, for this current meal
	philo->meal_count++; //Increment to indicate the philo have eaten a/another meal
	ph_status(EATING, philo); //Print the status
	ft_usleep(philo->data->time_to_eat, philo->data); //Introduce a delay to simulate the `time_to_eat` the philo spends eating
	if (philo->data->meals_total > 0 && philo->meal_count == philo->data->meals_total) //TODO comment
		set_bool(&philo->ph_mutex, &philo->max_meals, true);
	handle_mutex(&philo->left_fork->fork_mutex, UNLOCK);
	handle_mutex(&philo->right_fork->fork_mutex, UNLOCK);
}

//Define a function where the current thread/philo eats, sleeps, thinks
static void	*dining_philos(void *ph_data)
{
	t_ph	*philo; //A pointer variable for each philo struct 

	philo = (t_ph *)ph_data; //`ph_data` will represent `&data->philos_arr[i]`. In other words, philo will be the `i`th philo
	wait_all_threads(philo->data); //Wait for `threads_ready` to become true before all philos can execute concurrently (start simulation)
	//set_long(&philo->ph_mutex, &philo->meal_time, gettime(MILLISECONDS));
	//increase_long(&philo->data->access_mutex, &philo->data->threads_running_nbr); //TODO
	//de_synchronize_philos(philo); //TODO
	while (!get_bool(&philo->data->access_mutex, &philo->data->end_time)) //Loop until `end_time` is true
	{
		if (get_bool(&philo->ph_mutex, &philo->max_meals)) //If `max_meals` is true, break out of loop
			break ;
		eating(philo); //TODO
		write_status(SLEEPING, philo); //Print `philo is sleeping`
		ft_usleep(philo->data->time_to_sleep, philo->data); //Introduce a sleep duration for the current philo between eating and thinking. See #1
		thinking(philo, false); //TODO
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
	/*else if (data->ph_total == 1) //Handle a single philo //TODO
		handle_thread(&data->philos_arr[0].ph_thread, lone_philo,
			&data->philos_arr[0], CREATE);*/
	else //If there are more than 1 philos, create each of their threads
		while (i < data->ph_total) //dining_philos() is passed for each philo to execute concurrently (when `threads_ready` = true)
		{
			handle_thread(&data->philos_arr[i].ph_thread, dining_philos, &data->philos_arr[i], CREATE);
			i++;
		}
	//handle_thread(&data->monitor, monitor_dinner, data, CREATE); 
	data->start_time = gettime(MILLISECONDS); //Record the start time of the simulation in milliseconds as required
	set_bool(&data->access_mutex, &data->threads_ready, true); //Set to true to indicate all the threads are ready to start
	//Simulation starts here
	i = 0;
	while (i < data->ph_total) //For each philo
		handle_thread(&data->philos_arr[i++].ph_thread, NULL, NULL, JOIN); //Wait (join()) for the current philo/thread to finish its execution, e.g. complete their max_meals
	set_bool(&data->access_mutex, &data->end_time, true); //TODO comment
	handle_thread(&data->monitor, NULL, NULL, JOIN);
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