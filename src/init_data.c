/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:20:12 by ebalana-          #+#    #+#             */
/*   Updated: 2025/03/25 13:08:03 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		pthread_mutex_init(&data->philos[i].left_fork, NULL);
		if (data->num_philos == 1)
			data->philos[0].right_fork = NULL; // No funcionaria he de fer una funcio nomes on agafi una furquilla y mori perque no troba mes forquilles 
		else if (i == 0)
			data->philos[i].right_fork = \
			&data->philos[data->num_philos - 1].left_fork;
		else
			data->philos[i].right_fork = &data->philos[i - 1].left_fork;
		data->philos[i].data = data;	
		/*
		printf("Philosopher %d -> Left Fork: %p | Right Fork: %p\n",
			data->philos[i].id,
			(void *)&data->philos[i].left_fork,
			(void *)data->philos[i].right_fork);
		*/
		i++;
	}
	return (1);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->someone_died = 0;
	data->start_time = get_current_time();
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (free_data(data), NULL);
	if (!init_philosophers(data))
		return (free_data(data), NULL);
	printf(FILO_INI, data->num_philos);
	return (data);
}
