/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:00:09 by adrian            #+#    #+#             */
/*   Updated: 2025/07/25 17:38:32 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_sleep(10);
	if (philo->table->n_philos == 1)
	{
		lock_forks(philo);
		check_end(philo);
		return (NULL);
	}
	while (42)
	{
		if (check_end(philo))
			break ;
		lock_forks(philo);
		eat(philo);
		release_forks(philo);
		if (check_end(philo))
			break ;
		rest(philo);
	}
	return (NULL);
}

void	lock_forks(t_philo *philo)
{
	if (philo->table->n_philos == 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_status(philo, "not enought forks");
		ft_sleep(philo->table->td);
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	}
	else
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
			pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		}
		else
		{
			pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
			pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		}
		print_status(philo, "has taken right fork");
		print_status(philo, "has taken left fork");
	}
}

void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->table->check_mutex);
	philo->time_since_eat = get_current_time();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->table->check_mutex);
	if (sleep_or_die(philo, philo->table->te))
		return ;
	ft_sleep(philo->table->te);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void	rest(t_philo *philo)
{
	print_status(philo, "is sleeping");
	if (sleep_or_die(philo, philo->table->ts))
		return ;
	ft_sleep(philo->table->ts);
	print_status(philo, "is thinking");
}
