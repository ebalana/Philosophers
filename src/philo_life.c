/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:49:57 by ebalana-          #+#    #+#             */
/*   Updated: 2025/03/25 17:40:59 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Función que imprime el estado del filósofo
void	print_status(t_philo *philo, const char *status, int meals_eaten)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (my_strcmp(status, "está comiendo") == 0)
	{
		printf("%ld: Filósofo %d %s (%d 🍝)\n", get_current_time() -
		philo->data->start_time, philo->id, status, meals_eaten);
	} else 
	{
		printf("%ld: Filósofo %d %s\n", get_current_time() - 
		philo->data->start_time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}

// Filósofo piensa antes de comer
void	think(t_philo *philo)
{
	print_status(philo, "está pensando", 0);
}

// Filósofo toma los tenedores
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_status(philo, "tomó su tenedor izquierdo", 0);

	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "tomó su tenedor derecho", 0);
}

// Filósofo come
void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	print_status(philo, "está comiendo", philo->meals_eaten);
	if (philo->data->must_eat != -1 && philo->meals_eaten >= philo->data->must_eat)
		philo->data->must_eat--;
	pthread_mutex_unlock(&philo->data->death_mutex);
	usleep(philo->data->time_to_eat * 1000); 
}

// Filósofo suelta los tenedores
void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_status(philo, "soltó sus tenedores", 0);
}

// Filósofo duerme después de comer
void	sleep_philo(t_philo *philo)
{
	print_status(philo, "está durmiendo 🛌", 0);
	usleep(philo->data->time_to_sleep * 1000);
}

// Verifica si el filósofo ha muerto
void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (get_current_time() - philo->last_meal_time > philo->data->time_to_die)
	{
		philo->data->someone_died = 1;
		print_status(philo, "ha muerto 💀", 0);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

// Función que gestiona la rutina del filósofo
void	*philolife(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	// Espera hasta el tiempo de inicio
	while (get_current_time() < philo->data->start_time)
		usleep(100);  // Esto es para asegurar que todos los filósofos inicien a la vez
	print_status(philo, "se ha activado", 0);
	// Rutina principal de los filósofos
	while (!philo->data->someone_died && (philo->meals_eaten < philo->data->must_eat || philo->data->must_eat == -1))
	{
		think(philo);	  // Pensar
		take_forks(philo); // Tomar tenedores
		eat(philo);		// Comer
		put_forks(philo);  // Soltar tenedores
		sleep_philo(philo); // Dormir
		check_death(philo); // Verificar si ha muerto
	}
	return (NULL);
}

// Inicializa los hilos de los filósofos
int init_threads(t_data *data)
{
	pthread_t *threads;
	int i = 0;

	threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!threads)
		return 0;
	// Crear los hilos de los filósofos
	while (i < data->num_philos)
	{
		if (pthread_create(&threads[i], NULL, philolife, &data->philos[i]) != 0)
		{
			printf("Error creando el hilo del filósofo %d\n", i);
			free(threads);
			return (0);
		}
		i++;
	}
	// Establecer el tiempo de inicio para sincronización
	data->start_time = get_current_time() + 10; // 10ms de margen para asegurar sincronización
	// Esperar a que todos los filósofos terminen
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (1);
}

