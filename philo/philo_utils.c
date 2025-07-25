/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:30:16 by adrian            #+#    #+#             */
/*   Updated: 2025/07/25 18:33:22 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo, long time_in_ms)
{
	long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time_in_ms)
	{
			pthread_mutex_lock(&philo->table->check_mutex);
			if (philo->table->someone_died)
			{
					pthread_mutex_unlock(&philo->table->check_mutex);
					break ;
			}
			pthread_mutex_unlock(&philo->table->check_mutex);
			usleep(100);
	}
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		if (result > 2147483647 && sign == 1)
			return (-1);
		if (result > 2147483648 && sign == -1)
			return (0);
		i++;
	}
	return ((int)(result * sign));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	safe_exit(t_table *table, int status)
{
	printf("Error\n");
	if (table)
	{
		if (table->forks)
			free(table->forks);
		if (table->philo)
			free(table->philo);
	}
	return (status);
}
