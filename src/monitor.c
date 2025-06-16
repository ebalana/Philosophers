/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:45:26 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/22 14:29:14 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_message(char *str, t_philo *philo, int id, int meals)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
	{
		if (my_strcmp(str, "is eating") == 0)
		{
			printf("%zu: %d %s (%d 🍝)\n", time, philo->id, str, meals);
		}
		else
			printf("%zu: %d %s\n", time, id, str);
	}
	pthread_mutex_unlock(philo->write_lock);
}

int	philo_dead(t_philo *philo, size_t time_to_die)
{
	size_t	current_time;
	size_t	last_meal_time;
	int		is_eating;

	pthread_mutex_lock(philo->meal_lock);
	current_time = get_current_time();
	last_meal_time = philo->last_meal;
	is_eating = philo->eating;
	pthread_mutex_unlock(philo->meal_lock);
	if (current_time - last_meal_time >= time_to_die && is_eating == 0)
		return (1);
	return (0);
}

int	check_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_philos)
	{
		if (philo_dead(&philos[i], philos[i].time_to_die))
		{
			print_message("died 💀", &philos[i], philos[i].id, 0);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos[i].dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished_eating == philos[0].num_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (check_dead(philos) == 1 || check_ate(philos) == 1)
			break ;
		usleep(100);
	}
	return (pointer);
}
