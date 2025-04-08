/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:51:39 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/08 11:53:48 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!check_args(argc, argv))
		return (1);
	printf(VALID_ARG);
	data = init_data(argc, argv);
	if (!data)
	{
		if (ft_atoi(argv[2]) == 1)
			return (printf(ERROR_DATA), 1);
		else
			return (1);
	}
	if (!init_threads(data))
	{
		free_data(data);
		return (printf(ERROR_THREAD), 1);
	}
	free_data(data);
	return (0);
}
