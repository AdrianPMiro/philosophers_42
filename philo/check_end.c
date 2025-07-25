/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:36:42 by adrian            #+#    #+#             */
/*   Updated: 2025/07/25 18:37:01 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define YUMMY "All philosophers have eaten enough ñam ñam"

int	sleep_or_die(t_philo *philo, long action_time)
{
	long	now;
	long	time_left;

	pthread_mutex_lock(&philo->table->check_mutex);
	now = get_current_time();
	time_left = philo->table->td - (now - philo->time_since_eat);
	pthread_mutex_unlock(&philo->table->check_mutex);
	if (time_left <= 0)
	{
		print_status(philo, "died");
		return (1);
	}
	if (time_left < action_time)
	{
		ft_sleep(philo,time_left);
		print_status(philo, "died");
		return (1);
	}
	return (0);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->print_locks);
	pthread_mutex_lock(&philo->table->check_mutex);
	if (!philo->table->someone_died)
	{
		timestamp = get_current_time() - philo->table->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
		if (ft_strcmp(status, "died") == 0
			|| ft_strcmp(status, YUMMY) == 0)
			philo->table->someone_died = 1;
	}
	pthread_mutex_unlock(&philo->table->check_mutex);
	pthread_mutex_unlock(&philo->table->print_locks);
}

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	check_philosopher(t_philo *current_philo, t_philo *philo)
{
	if ((get_current_time() - current_philo->time_since_eat) >= philo->table->td)
	{
		pthread_mutex_unlock(&philo->table->check_mutex);
		print_status(current_philo, "died");
		return (1);
	}
	if ((philo->table->min_meals != -1)
		&& current_philo->meals_count < philo->table->min_meals)
		philo->table->all_finish = 0;
	return (0);
}

int	check_end(t_philo *philo)
{
	int	index;

	pthread_mutex_lock(&philo->table->check_mutex);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->check_mutex);
		return (1);
	}
	philo->table->all_finish = 1;
	index = 0;
	while (index < philo->table->n_philos)
	{
		if (check_philosopher(&philo->table->philo[index], philo))
			return (1);
		index++;
	}
	if (philo->table->all_finish && philo->table->min_meals != -1)
	{
		pthread_mutex_unlock(&philo->table->check_mutex);
		print_status(philo, YUMMY);
		return (1);
	}
	index = philo->table->someone_died;
	pthread_mutex_unlock(&philo->table->check_mutex);
	return (index);
}
