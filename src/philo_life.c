/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:49:57 by ebalana-          #+#    #+#             */
/*   Updated: 2025/03/25 13:12:01 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Espera hasta que la simulación comience
void wait_for_start(t_data *data)
{
    while (get_current_time() < data->start_time)
        usleep(100);
}

// Filósofo piensa antes de comer
void think(t_philo *philo)
{
    printf("Filósofo %d está pensando\n", philo->id);
    usleep(1000);
}

// Filósofo toma los tenedores
void take_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork);
    printf("Filósofo %d tomó su tenedor izquierdo\n", philo->id);

    pthread_mutex_lock(philo->right_fork);
    printf("Filósofo %d tomó su tenedor derecho\n", philo->id);
}

// Filósofo come
void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death_mutex);
    philo->last_meal_time = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->death_mutex);

    printf("Filósofo %d está comiendo (%d comidas)\n", philo->id, philo->meals_eaten);
    usleep(philo->data->time_to_eat * 1000);
}

// Filósofo suelta los tenedores
void put_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    printf("Filósofo %d soltó sus tenedores\n", philo->id);
}

// Filósofo duerme después de comer
void sleep_philo(t_philo *philo)
{
    printf("Filósofo %d está durmiendo\n", philo->id);
    usleep(philo->data->time_to_sleep * 1000);
}

// Verifica si el filósofo murió
void check_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death_mutex);
    if (get_current_time() - philo->last_meal_time > philo->data->time_to_die)
    {
        philo->data->someone_died = 1;
        printf("💀 Filósofo %d ha muerto 💀\n", philo->id);
    }
    pthread_mutex_unlock(&philo->data->death_mutex);
}


void	*philolife(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	// Esperar hasta el tiempo de inicio
	wait_for_start(philo->data);

	philo->activation_time = get_current_time();
	printf("Filósofo %d activado en %ld ms\n", philo->id, philo->activation_time);

	while (!philo->data->someone_died || !philo->data->must_eat)
	{
		think(philo);       // Pensar
		take_forks(philo);  // Tomar tenedores
		eat(philo);         // Comer
		put_forks(philo);   // Soltar tenedores
		sleep_philo(philo); // Dormir
		check_death(philo); // Revisar si ha muerto
	}

	return (NULL);
}

int	init_threads(t_data *data)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!threads)
		return (0);

	i = 0;
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

	// Establece el tiempo de inicio para sincronización
	data->start_time = get_current_time() + 10; // 10ms de margen

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}

	free(threads);
	return (1);
}
