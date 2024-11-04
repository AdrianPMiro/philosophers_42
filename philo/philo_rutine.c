/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:00:09 by adrian            #+#    #+#             */
/*   Updated: 2024/11/05 00:36:03 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// En philo_rutine.c
void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // Si el ID del filósofo es par, esperar un poco para evitar interbloqueo
    if (philo->id % 2 == 0)
        ft_sleep(10);

    while (1)
    {
        // Verificar si se debe terminar antes de actuar
        pthread_mutex_lock(&philo->table->check_mutex);
        if (philo->table->someone_died)
        {
            pthread_mutex_unlock(&philo->table->check_mutex);
            break; // Salir del ciclo después de desbloquear
        }
        pthread_mutex_unlock(&philo->table->check_mutex);

        lock_forks(philo);
        eat(philo);
        release_forks(philo);

        // Verificar nuevamente después de comer
        if (check_end(philo))
            break;

        rest(philo);
    }
    return NULL;
}

void lock_forks(t_philo *philo)
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
    print_status(philo, "has taken a fork");
}

void eat(t_philo *philo)
{
    print_status(philo, "is eating");
    philo->time_since_eat = get_current_time();
    philo->meals_count++;
    ft_sleep(philo->table->te);
}

void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void rest(t_philo *philo)
{
    print_status(philo, "is sleeping");
    ft_sleep(philo->table->ts);
    print_status(philo, "is thinking");
}
