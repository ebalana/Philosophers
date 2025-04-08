/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:49:57 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/08 12:33:02 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status(t_philo *philo, const char *status, int meals_eaten)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (my_strcmp(status, "está comiendo") == 0)
	{
		printf("%ld: Filósofo %d %s (%d 🍝)\n", get_current_time() - \
		philo->data->start_time, philo->id, status, meals_eaten);
	}
	else
	{
		printf("%ld: Filósofo %d %s\n", get_current_time() - \
		philo->data->start_time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void *philolife(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (get_current_time() < philo->data->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 0.9);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		int should_stop = philo->data->someone_died || 
							(philo->data->must_eat != -1 && 
							philo->data->finished_philos >= philo->data->num_philos);
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (should_stop)
			break;
		if (!think(philo)) break;
		if (!take_forks(philo)) break;
		// if (!eat(philo)) break;
		if (!eat(philo)) {
			put_forks(philo); // Libera los tenedores aunque mueras comiendo
			break;
		}
		if (!put_forks(philo)) break;
		if (!sleep_philo(philo)) break;
	}
	printf("🧵 Filósofo %d ha salido de su rutina\n", philo->id);
	return (NULL);
}


int	create_observer_thread(t_data *data, pthread_t *observer_thread)
{
	if (pthread_create(observer_thread, NULL, observer, data) != 0)
	{
		printf(ERROR_THREAD_OBSER);
		return (0);
	}
	return (1);
}

int	create_philo_threads(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&threads[i], NULL, philolife, &data->philos[i]) != 0)
		{
			printf(ERROR_THREAD_PHILO, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_threads(t_data *data)
{
	pthread_t	*threads;
	pthread_t	observer_thread;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!threads)
		return (0);
	if (!create_philo_threads(data, threads))
		return (free(threads), 0);
	if (!create_observer_thread(data, &observer_thread))
		return (free(threads), 0);
	data->start_time = get_current_time() + 10;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(threads[i], NULL);
		printf("✅ Joined hilo Filósofo %d\n", i);
		i++;
	}
	pthread_join(observer_thread, NULL);
	printf("✅ Joined hilo Observador\n");
	free(threads);
	return (1);
}