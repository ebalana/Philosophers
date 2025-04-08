/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:00:23 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/03 16:24:54 by ebalana-         ###   ########.fr       */
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

void	*one_philo_routine(void *arg)
{
	t_philo	*philo;
	long	start;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	if (!philo->data)
		return (NULL);
	start = get_current_time();
	printf(FILO_INI, philo->data->num_philos);
	printf(ONE_PHILO, get_current_time() - start);
	usleep(philo->data->time_to_die * 1000);
	printf("%d Filosofo 0 ha muerto 💀\n", philo->data->time_to_die);
	return (NULL);
}

int	one_philo(t_data *data)
{
	pthread_t	thread;

	data->philos[0].id = 0;
	data->philos[0].meals_eaten = 0;
	data->philos[0].last_meal_time = data->start_time;
	data->philos[0].data = data;
	pthread_create(&thread, NULL, one_philo_routine, &data->philos[0]);
	pthread_join(thread, NULL);
	return (0);
}

/*
int one_philo(t_data *data)
{
    long start = get_current_time();
    
    printf("%ld 0 tomó su tenedor izquierdo\n", 0);
    usleep(data->time_to_die * 1000);
    printf("%d 0 ha muerto 💀\n", data->time_to_die);
    
    // Forzar terminación de todo el programa
    pthread_mutex_lock(&data->death_mutex);
    data->someone_died = 1;
    pthread_mutex_unlock(&data->death_mutex);
    
    return (1);
}
*/