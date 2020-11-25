/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 00:16:20 by gbaud             #+#    #+#             */
/*   Updated: 2020/11/25 02:17:14 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/global.h"

void *run(void *p)
{
    t_philo *philo;

    philo = (t_philo *)p;
    while(1)
    {
        ft_putnbr(philo->id);
        ft_putstr("\n");
    }
}