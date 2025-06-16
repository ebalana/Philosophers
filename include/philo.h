/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:53:04 by ebalana-          #+#    #+#             */
/*   Updated: 2025/03/12 13:40:55 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>

# define PHILO_MAX 200

# define ERROR_ARG				"Incorrect number of arguments\n"
# define ERROR_ARG_INVALID		"Invalid argument: %s\n"
# define VALID_ARG				"All arguments are valid\n"
# define FILO_INI				"%d Philosophers initialized\n"
# define ERROR_THREAD_OBSER		"Error creating observer thread\n"
# define ERROR_THREAD_PHILO		"Error creating philosopher thread\n"
# define ERROR_JOIN				"Error joining threads\n"

typedef struct s_program	t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	t_program		*program;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

// main.c
int		ft_atoi(char *str);
int		check_args(int argc, char **argv);

// init.c
void	init_program(t_program *program, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
			char **argv);

// thread.c
int		dead_loop(t_philo *philo);
void	*philo_routine(void *pointer);
int		thread_create(t_program *program, pthread_mutex_t *forks);

// monitor.c
void	print_message(char *str, t_philo *philo, int id, int meals);
int		philo_dead(t_philo *philo, size_t time_to_die);
int		check_ate(t_philo *philos);
int		check_dead(t_philo *philos);
void	*monitor(void *pointer);

// routine.c
void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);

// utils.c
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
int		ft_strlen(char *str);
void	destory_all(char *str, t_program *program, pthread_mutex_t *forks);
int		my_strcmp(const char *str1, const char *str2);

#endif