/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:36:42 by adrian            #+#    #+#             */
/*   Updated: 2024/11/05 00:37:39 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void ft_sleep(long time_in_ms)
{
    long start_time;
    start_time = get_current_time();
    while ((get_current_time() - start_time) < time_in_ms)
        usleep(100);
}

void print_status(t_philo *philo, char *status)
{
    long timestamp;

    pthread_mutex_lock(&philo->table->print_locks);
    timestamp = get_current_time() - philo->table->start_time;

    if (!philo->table->someone_died)
    {
        printf("%ld %d %s\n", timestamp, philo->id, status);
        if (strcmp(status, "died") == 0)
        {
            philo->table->someone_died = 1; // Actualizar la bandera en caso de muerte
        }
        else if (strcmp(status, "All philosophers have eaten enough ñam ñam") == 0)
        {
            philo->table->someone_died = 1; // Reutilizar la bandera para indicar finalización exitosa
        }
    }

    pthread_mutex_unlock(&philo->table->print_locks);
}

long get_current_time()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

// En check_end.c
int check_end(t_philo *philo)
{
    int index;

    pthread_mutex_lock(&philo->table->check_mutex);

    // Si alguien ya ha muerto o todos han terminado, retornar
    if (philo->table->someone_died)
    {
        pthread_mutex_unlock(&philo->table->check_mutex);
        return (1);
    }

    philo->table->all_finish = 1;
    index = 0;
    while (index < philo->table->n_philos)
    {
        t_philo *current_philo = &philo->table->philo[index];

        // Comprobar si el filósofo ha muerto
        if ((get_current_time() - current_philo->time_since_eat) > philo->table->td)
        {
            print_status(current_philo, "died");
            pthread_mutex_unlock(&philo->table->check_mutex);
            return (1);
        }

        // Comprobar si todos han alcanzado el número mínimo de comidas
        if ((philo->table->min_meals != -1) &&
            current_philo->meals_count < philo->table->min_meals)
        {
            philo->table->all_finish = 0;
        }
        index++;
    }

    // Si todos han comido suficiente, actualizar la bandera
    if (philo->table->all_finish && philo->table->min_meals != -1)
    {
        print_status(philo, "All philosophers have eaten enough ñam ñam");
    }

    pthread_mutex_unlock(&philo->table->check_mutex);
    return (philo->table->someone_died);
}
