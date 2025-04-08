/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:16:53 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/08 12:36:55 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void check_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->meal_mutex);
    
    if (philo->data->must_eat == -1 || philo->meals_eaten < philo->data->must_eat)
    {
        long time_since_meal = get_current_time() - philo->last_meal_time;
        if (time_since_meal >= philo->data->time_to_die)
        {
            pthread_mutex_lock(&philo->data->death_mutex);
            if (!philo->data->someone_died)
            {
                philo->data->someone_died = 1;
                print_status(philo, "ha muerto 💀", 0);
            }
            pthread_mutex_unlock(&philo->data->death_mutex);
        }
    }
    pthread_mutex_unlock(&philo->data->meal_mutex);
}

void *observer(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    printf("🧐 Hilo del observador iniciado\n");

    while (1)
    {
        i = 0;
        while (i < data->num_philos)
        {
            check_death(&data->philos[i]);
            pthread_mutex_lock(&data->death_mutex);
            
            if (data->someone_died)
            {
                pthread_mutex_unlock(&data->death_mutex);
                printf("💀 El observador detectó una muerte, finalizando hilo\n"); // 👈 Debug
                return (NULL);  // Terminar si hay una muerte
            }

            if (data->must_eat != -1 && data->finished_philos >= data->num_philos)
            {
                pthread_mutex_unlock(&data->death_mutex);
                printf("✅ El observador detectó que todos los filósofos han comido, finalizando hilo\n");
                return (NULL); 
            }
            
            pthread_mutex_unlock(&data->death_mutex);
            i++;
        }
        usleep(1000);  // Pequeño delay para no sobrecargar la CPU
    }
    printf("👋 El hilo del observador ha finalizado\n");
    return (NULL);
}
