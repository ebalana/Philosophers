/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:16:53 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/02 14:19:37 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_death(t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->data->meal_mutex);
	time_since_last_meal = get_current_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_died && \
		time_since_last_meal >= philo->data->time_to_die)
	{
		philo->data->someone_died = 1;
		print_status(philo, "ha muerto 💀", 0);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

void	*observer(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->someone_died)
	{
		i = 0;
		while (i < data->num_philos && !data->someone_died)
		{
			check_death(&data->philos[i]);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
