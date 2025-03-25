/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:57:48 by ebalana-          #+#    #+#             */
/*   Updated: 2025/03/25 12:40:53 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (-1);
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return ((int)result);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (printf(ERROR_ARG), 0);
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0 || ft_atoi(argv[i]) == -1)
			return (printf(ERROR_ARG_INVALID, argv[i]), 0);
		i++;
	}
	return (1);
}
