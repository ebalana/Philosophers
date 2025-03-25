/* ************************************************************************** */
/*	                                                                        */
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

#include <time.h>

# define ERROR_ARG			"Error: Número incorrecto de argumentos\n"
# define ERROR_ARG_INVALID	"Error: Argumento inválido: %s\n"
# define VALID_ARG			"Todos los argumentos son válidos ✅\n"
# define ERROR_DATA			"Error: Falló la inicialización de datos\n"
# define FILO_INI			"%d Filósofos inicializados ✅\n"
# define ERROR_THREAD		"Error creando el hilo del filósofo\n"

struct	s_data;

typedef struct	s_philo
{
	long			creation_time; //test
	long			activation_time; //test
	int				id;
	int				meals_eaten;
	long			last_meal_time; // Última vez que comió (en milisegundos)
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data; // Usamos struct s_data en lugar de t_data para inicializarlo antes
}	t_philo;

typedef struct	s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			start_time;		// Tiempo de inicio de la simulación (en milisegundos)
	int				someone_died;	// Flag para detener la simulación si un filósofo muere
	pthread_mutex_t	death_mutex;	// Protege el acceso a someone_died
	pthread_mutex_t	write_mutex;	// Protege la impresión en consola
	t_philo			*philos;
}	t_data;

// check.c
int		is_digit(char c);
int		ft_atoi(const char *str);
int		check_args(int argc, char **argv);

//free.c
void	free_data(t_data *data);

// init_data.c
long	get_current_time(void);
int		init_philosophers(t_data *data);
t_data	*init_data(int argc, char **argv);

//philo_life.c
void	*philolife(void *arg);
int		init_threads(t_data *data);

#endif
