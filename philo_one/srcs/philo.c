/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 00:16:20 by gbaud             #+#    #+#             */
/*   Updated: 2020/11/25 16:25:14 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/global.h"

void    take_fork(t_philo *p)
{
        pthread_mutex_lock(p->mutex_lock);
        pthread_mutex_lock(&p->fork[p->id]);
        log_action(p, "is taken a fork");
        pthread_mutex_lock(&p->fork[(p->id + 1) % p->nop]);
        log_action(p, "is taken a fork");
        pthread_mutex_unlock(p->mutex_lock);
}

void    free_fork(t_philo *p)
{
        pthread_mutex_unlock(&p->fork[p->id]);
        pthread_mutex_unlock(&p->fork[(p->id + 1) % p->nop]);
}

void    philo_eat(t_philo *p)
{
        log_action(p, "is eating");
        p->eat--;
        p->ttd = get_time_ms() + p->ittd;
        usleep(p->itte * 1000);
}

void    philo_sleep(t_philo *p)
{
        log_action(p, "is sleeping");
        usleep(p->itts * 1000);
}

void *run(void *s)
{
    t_philo *philo;

    philo = (t_philo *)s;
    while (philo->eat != 0)
    {
        take_fork(philo);
        philo_eat(philo);
        free_fork(philo);
        philo_sleep(philo);
        log_action(philo, "is thinking");
    }
    philo->ttd = -1;
    free_fork(philo);
    return (NULL);
}