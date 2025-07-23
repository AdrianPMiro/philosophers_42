/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:40:02 by adrian            #+#    #+#             */
/*   Updated: 2025/07/23 16:54:48 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	int		status;

	if (ac != 5 && ac != 6)
		return (printf("Bad usage: %s\n", av[0]));
	status = init_table(&table, ac, av);
	if (status)
		return (status);
	status = start_table(&table);
	clean_table(&table);
	return (status);
}

int	init_av(t_table *table, int ac, char **av)
{
	table->forks = NULL;
	table->philo = NULL;
	if (!av[1] || !av[2] || !av[3] || !av[4] || (ac != 5 && ac != 6))
		return (safe_exit(table, 1));
	table->n_philos = ft_atoi(av[1]);
	table->td = ft_atoi(av[2]);
	table->te = ft_atoi(av[3]);
	table->ts = ft_atoi(av[4]);
	table->min_meals = -1;
	table->someone_died = 0;
	if (ac == 6)
		table->min_meals = ft_atoi(av[5]);
	if (table->n_philos <= 0 || table->td <= 0 || table->te <= 0
		|| table->ts <= 0 || (ac == 6 && table->min_meals <= 0))
		return (safe_exit(table, 1));
	return (0);
}

int	init_table(t_table *table, int ac, char **av)
{
	if (init_av(table, ac, av))
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	table->philo = malloc(sizeof(t_philo) * table->n_philos);
	if (!table->forks || !table->philo)
		return (safe_exit(table, -1));
	table->i = 0;
	while (table->i < table->n_philos)
		pthread_mutex_init(&table->forks[table->i++], NULL);
	pthread_mutex_init(&table->print_locks, NULL);
	pthread_mutex_init(&table->check_mutex, NULL);
	table->start_time = get_current_time();
	table->i = 0;
	while (table->i < table->n_philos)
	{
		table->philo[table->i].id = table->i + 1;
		table->philo[table->i].is_dead = 0;
		table->philo[table->i].time_since_eat = table->start_time;
		table->philo[table->i].meals_count = 0;
		table->philo[table->i].table = table;
		table->philo[table->i].left_fork = table->i;
		table->philo[table->i].right_fork = (table->i + 1) % table->n_philos;
		table->i++;
	}
	return (0);
}

int	start_table(t_table *table)
{
	table->i = 0;
	while (table->i < table->n_philos)
	{
		if (pthread_create(&table->philo[table->i].thread,
				NULL, &philo_routine, &table->philo[table->i]))
			return (safe_exit(table, -1));
		table->i++;
	}
	table->i = 0;
	while (table->i < table->n_philos)
	{
		if (pthread_join(table->philo[table->i].thread, NULL))
			return (safe_exit(table, -1));
		table->i++;
	}
	return (0);
}

void	clean_table(t_table *table)
{
	table->i = 0;
	while (table->i < table->n_philos && table->forks)
		pthread_mutex_destroy(&table->forks[table->i++]);
	pthread_mutex_destroy(&table->print_locks);
	pthread_mutex_destroy(&table->check_mutex);
	if (table->forks)
		free(table->forks);
	if (table->philo)
		free(table->philo);
}
