/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:39:57 by adrian            #+#    #+#             */
/*   Updated: 2025/04/23 14:06:42 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				is_dead;
	int				left_fork;
	int				right_fork;
	long			time_since_eat;
	int				current_time;
	int				meals_count;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				i;
	int				n_philos;
	int				td;
	int				te;
	int				ts;
	int				min_meals;
	int				all_finish;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_locks;
	pthread_mutex_t	check_mutex;
	t_philo			*philo;
	//int			program_should_exit;
} t_table;

//main 
int		init_table(t_table *table, int ac, char **av);
int		start_table(t_table *table);
int		init_av(t_table *table, int ac, char **av);
void	clean_table(t_table *table);

//rutine
void	*philo_routine(void *arg);
void	lock_forks(t_philo *philo);
void	eat(t_philo *philo);
void	release_forks(t_philo *philo);
void	rest(t_philo *philo);

//utils
int		check_end(t_philo *philo);
long	get_current_time(void);
void	ft_sleep(long time_in_ms);
void	print_status(t_philo *philo, char *status);
int		safe_exit(t_table *table, int status);

int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *nptr);
#endif