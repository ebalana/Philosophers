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

# define ERROR_ARG				"Error: Número incorrecto de argumentos\n"
# define ERROR_ARG_INVALID		"Error: Argumento inválido: %s\n"
# define VALID_ARG				"Todos los argumentos son válidos ✅\n"
# define ERROR_DATA				"Error: Falló la inicialización de datos\n"
# define FILO_INI				"%d Filósofos inicializados ✅\n"
# define ERROR_THREAD			"Error creando los hilos\n"
# define ERROR_THREAD_PHILO		"Error creando el hilo del filósofo %d\n"
# define ERROR_THREAD_OBSER		"Error creando el hilo del observador\n"
# define ONE_PHILO				"%ld Filosofo 0 tomó su tenedor izquierdo\n"

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				finished_philos;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	write_mutex;
	t_philo			*philos;
	pthread_t		observer;
}	t_data;

// check.c
int		is_digit(char c);
int		ft_atoi(const char *str);
int		check_args(int argc, char **argv);

//free.c
void	free_data(t_data *data);
int		my_strcmp(const char *str1, const char *str2);
void	*one_philo_routine(void *arg);
int		one_philo(t_data *data);

// init_data.c
long	get_current_time(void);
int		init_philosophers(t_data *data);
t_data	*init_data(int argc, char **argv);

//philo_life.c
void	print_status(t_philo *philo, const char *status, int meals_eaten);
int		create_philo_threads(t_data *data, pthread_t *threads);
int		create_observer_thread(t_data *data, pthread_t *observer_thread);
void	*philolife(void *arg);
int		init_threads(t_data *data);

//routine.c
int	think(t_philo *philo);
int	take_forks(t_philo *philo);
int	eat(t_philo *philo);
int	put_forks(t_philo *philo);
int	sleep_philo(t_philo *philo);

//observer.c
void	check_death(t_philo *philo);
void	*observer(void *arg);

#endif
