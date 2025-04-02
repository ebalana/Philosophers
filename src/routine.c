/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:14:54 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/02 14:17:19 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	think(t_philo *philo)
{
	print_status(philo, "está pensando", 0);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_status(philo, "tomó su tenedor izquierdo", 0);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "tomó su tenedor derecho", 0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->meals_eaten++;
	print_status(philo, "está comiendo", philo->meals_eaten);
	if (philo->meals_eaten == philo->data->must_eat)
		philo->data->finished_philos++;
	pthread_mutex_unlock(&philo->data->death_mutex);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_status(philo, "soltó sus tenedores", 0);
}

void	sleep_philo(t_philo *philo)
{
	print_status(philo, "está durmiendo 🛌", 0);
	usleep(philo->data->time_to_sleep * 1000);
}
