/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:00:23 by ebalana-          #+#    #+#             */
/*   Updated: 2025/03/12 18:04:51 by ebalana-         ###   ########.fr       */
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
		free(data);
	}
}
