/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 23:29:03 by tquemato          #+#    #+#             */
/*   Updated: 2024/04/30 23:33:06 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//ANSI Escape Sequences for text formatting*****
# define RESET		"\033[0m" //Reset to default color 
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[1;37m"

//DATA STRUCTS*****
typedef struct s_data	t_data;

//Define t_mtx here to use its shortened name throughout our codes
typedef pthread_mutex_t	t_mtx;

//For each fork
typedef struct s_fork
{
	t_mtx		fork_mutex;
	int			fork_id;
}				t_fork;

//For each philosopher
typedef struct s_ph
{
	int			ph_id;
	long		meal_count;
	bool		max_meals;
	long		meal_time;
	pthread_t	ph_thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_mtx		ph_mutex;
	t_data		*data;
}				t_ph;

//For managing the rules of the mandatory part
typedef struct s_data
{
	long			ph_total;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_total;
	long			start_time;
	bool			end_time;
	bool			threads_ready;
	long			active_philos_count;
	pthread_t		death_check;
	t_fork			*forks_arr;
	t_ph			*philos_arr;
	t_mtx			access_mutex;
	t_mtx			write_mutex;
}					t_data;

//ENUMS*****

//For representing a philosoper's state during a simulation
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

//For representing thread and mutex functions for cleaner readability
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
void		*single_philo(void *index);

//THREADS & MUTEXES HANDLERS*****
void		handle_mutex(t_mtx *mtx, t_ftcode ftcode);
void		handle_thread(pthread_t *thread_info,
				void *(*foo)(void *),
				void *t_data,
				t_ftcode ftcode);

//PROTECT VARIABLES*****
void		set_bool(t_mtx	*mutex, bool *dst, bool value);
bool		get_bool(t_mtx *mutex, bool *value);
void		set_long(t_mtx *mutex, long *dst, long value);
long		get_long(t_mtx *mutex, long *value);

//MONITORING*****
void		wait_all_threads(t_data *data);
void		active_thread_counter(t_mtx *mutex, long *value);
void		*death_affirm(void *ph_data);
void		ph_status(t_ph_status status, t_ph *philo);

//UTILS*****
void		error_exit(const char *error_msg);
void		*ft_malloc(size_t bytes);
long		gettime(t_time_unit time_unit);
void		ft_usleep(long sleep_time, t_data *data);
void		free_things(t_data *data);

#endif