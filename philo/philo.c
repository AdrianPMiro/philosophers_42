/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:40:02 by adrian            #+#    #+#             */
/*   Updated: 2024/11/08 13:28:58 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (printf("Bad usage: %s\n", av[0]));
	init_table(&table, ac, av);
	start_table(&table);
	clean_table(&table);
	return (0);
}

void	init_av(t_table *table, int ac, char **av)
{
	if (av[1] == NULL || av[2] == NULL || av[3] == NULL || av[4] == NULL
		|| (ac != 5 && ac != 6))
		safe_exit(table, 1);
	table->n_philos = ft_atoi(av[1]);
	table->td = ft_atoi(av[2]);
	table->te = ft_atoi(av[3]);
	table->ts = ft_atoi(av[4]);
	table->min_meals = -1;
	table->someone_died = 0;
	if (ac == 6)
		table->min_meals = ft_atoi(av[5]);
	if (table->n_philos < 1 || table->td <= 0 || table->te <= 0
		||table->ts <= 0 || (ac == 6 && table->min_meals <= 0))
		safe_exit(table, 1);
}

void	init_table(t_table *table, int ac, char **av)
{
	init_av(table, ac, av);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	table->philo = malloc(sizeof(t_philo) * table->n_philos);
	if (table->forks == NULL || table->philo == NULL)
		safe_exit(table, -1);
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
}

void	start_table(t_table *table)
{
	table->i = 0;
	while (table->i < table->n_philos)
	{
		if (pthread_create(&table->philo[table->i].thread,
				NULL, &philo_routine, &table->philo[table->i]) != 0)
			safe_exit(table, -1);
		table->i++;
	}
	table->i = 0;
	while (table->i < table->n_philos)
	{
		if (pthread_join(table->philo[table->i].thread, NULL) != 0)
			safe_exit(table, -1);
		table->i++;
	}
}

void	clean_table(t_table *table)
{
	table->i = 0;
	while (table->i < table->n_philos)
		pthread_mutex_destroy(&table->forks[table->i++]);
	pthread_mutex_destroy(&table->print_locks);
	pthread_mutex_destroy(&table->check_mutex);
	if (table->forks != NULL)
		free(table->forks);
	if (table->philo != NULL)
		free(table->philo);
}
