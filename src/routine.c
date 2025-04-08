/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:14:54 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/08 12:34:33 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	think(t_philo *philo)
{
	print_status(philo, "está pensando", 0);
	return !philo->data->someone_died;
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_status(philo, "tomó su tenedor izquierdo", 0);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "tomó su tenedor derecho", 0);
	return !philo->data->someone_died;
}

int eat(t_philo *philo)
{
    // 1. Print antes de entrar al bucle (antes podía morir otro y aún así imprimías luego)
    pthread_mutex_lock(&philo->data->death_mutex);
    if (philo->data->someone_died)
    {
        pthread_mutex_unlock(&philo->data->death_mutex);
        return 0;
    }
    print_status(philo, "está comiendo", philo->meals_eaten + 1);
    pthread_mutex_unlock(&philo->data->death_mutex);

    // 2. Actualizar tiempo de última comida
    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->data->meal_mutex);

    // 3. Simular tiempo de comida
    long start = get_current_time();
    while (get_current_time() - start < philo->data->time_to_eat)
    {
        usleep(100);
        pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->someone_died)
        {
            pthread_mutex_unlock(&philo->data->death_mutex);
            return 0;
        }
        pthread_mutex_unlock(&philo->data->death_mutex);
    }

    // 4. Contador de comidas
    pthread_mutex_lock(&philo->data->death_mutex);
    philo->meals_eaten++;
    if (philo->data->must_eat != -1 && philo->meals_eaten >= philo->data->must_eat)
        philo->data->finished_philos++;
    pthread_mutex_unlock(&philo->data->death_mutex);

    return 1;
}

int	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_died)
		print_status(philo, "soltó sus tenedores", 0);
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (1); // Siempre true, ya soltaste
}

int sleep_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death_mutex);
    if (philo->data->someone_died)
    {
        pthread_mutex_unlock(&philo->data->death_mutex);
        return 0;
    }
    pthread_mutex_unlock(&philo->data->death_mutex);

    print_status(philo, "está durmiendo 🛌", 0);

    long start = get_current_time();
    while (get_current_time() - start < philo->data->time_to_sleep)
    {
        usleep(100);
        pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->someone_died)
        {
            pthread_mutex_unlock(&philo->data->death_mutex);
            return 0;
        }
        pthread_mutex_unlock(&philo->data->death_mutex);
    }
    return (1);
}

// int eat(t_philo *philo)
// {
//     // 1. Actualizar tiempo de última comida
//     pthread_mutex_lock(&philo->data->meal_mutex);
//     philo->last_meal_time = get_current_time();
//     pthread_mutex_unlock(&philo->data->meal_mutex);
    
//     // 2. Simular tiempo de comida CON verificaciones
//     long start = get_current_time();
//     while (get_current_time() - start < philo->data->time_to_eat)
//     {
//         usleep(100); // Pequeños sleeps para verificar frecuentemente
//         pthread_mutex_lock(&philo->data->death_mutex);
//         if (philo->data->someone_died)
//         {
//             pthread_mutex_unlock(&philo->data->death_mutex);
//             return 0;
//         }
//         pthread_mutex_unlock(&philo->data->death_mutex);
//     }
    
//     // 3. Actualizar estado
//     pthread_mutex_lock(&philo->data->death_mutex);
//     philo->meals_eaten++;
//     print_status(philo, "está comiendo", philo->meals_eaten);
    
//     if (philo->data->must_eat != -1 && philo->meals_eaten >= philo->data->must_eat)
//         philo->data->finished_philos++;
//     pthread_mutex_unlock(&philo->data->death_mutex);
    
//     return !philo->data->someone_died;
// }

// int	put_forks(t_philo *philo)
// {
// 	pthread_mutex_unlock(&philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);
// 	print_status(philo, "soltó sus tenedores", 0);
// 	return !philo->data->someone_died;
// }

// int	sleep_philo(t_philo *philo)
// {
// 	print_status(philo, "está durmiendo 🛌", 0);
// 	long start = get_current_time();
// 	while (get_current_time() - start < philo->data->time_to_sleep)
// 	{
// 		usleep(100);
// 		pthread_mutex_lock(&philo->data->death_mutex);
// 		if (philo->data->someone_died)
// 		{
// 			pthread_mutex_unlock(&philo->data->death_mutex);
// 			return 0;
// 		}
// 		pthread_mutex_unlock(&philo->data->death_mutex);
// 	}
// 	return 1;
// }
