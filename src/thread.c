/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:44:21 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/22 14:29:28 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (NULL);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	i = 0;
	while (i < program->philos[0].num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			destory_all(ERROR_THREAD_PHILO, program, forks);
		i++;
	}
	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		destory_all(ERROR_THREAD_OBSER, program, forks);
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destory_all(ERROR_JOIN, program, forks);
	while (i < program->philos[0].num_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destory_all(ERROR_JOIN, program, forks);
		i++;
	}
	return (0);
}
