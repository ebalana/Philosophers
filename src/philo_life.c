/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:49:57 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/02 14:34:48 by ebalana-         ###   ########.fr       */
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

void	*philolife(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_current_time() < philo->data->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_died)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->finished_philos == philo->data->num_philos)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		think(philo);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
	}
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
		i++;
	}
	pthread_join(observer_thread, NULL);
	free(threads);
	return (1);
}
