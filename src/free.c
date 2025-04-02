/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:00:23 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/02 16:18:58 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->philos)
		{
			while (i < data->num_philos)
			{
				pthread_mutex_destroy(&data->philos[i].left_fork);
				i++;
			}
			free(data->philos);
		}
		pthread_mutex_destroy(&data->write_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		pthread_mutex_destroy(&data->meal_mutex);
		free(data);
	}
}

int	my_strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			return (1);
		str1++;
		str2++;
	}
	if (*str1 != *str2)
		return (1);
	return (0);
}

int	one_philo(t_data *data)
{
	long	start;

	printf(FILO_INI, data->num_philos);
	start = get_current_time();
	printf(ONE_PHILO, get_current_time() - start);
	usleep(data->time_to_die * 1000);
	printf("%d Filosofo 0 ha muerto 💀\n", data->time_to_die);
	exit (0);
	return (1);
}
