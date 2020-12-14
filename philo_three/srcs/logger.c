/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@42lyon.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:25:59 by gbaud             #+#    #+#             */
/*   Updated: 2020/12/14 06:27:06 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/global.h"

void	log_died(t_simulation *simulation, int i)
{
	sem_wait(simulation->mutex);
	ft_putstr("\033[1;31m");
	ft_putnbr(get_time_ms());
	ft_putchar(' ');
	ft_putnbr(i + 1);
	ft_putstr(" died\n");
	ft_putstr("\033[1;30m");
}

void	log_end(t_simulation *simulation)
{
	sem_wait(simulation->mutex);
	ft_putstr("\033[1;32m");
	ft_putstr("====== End ======\n");
	ft_putstr("\033[0m");
}

int		log_action(t_philo *philo, char *str)
{
	sem_wait(philo->mutex);
	ft_putnbr(get_time_ms());
	ft_putstr("ms ");
	ft_putnbr(philo->id + 1);
	ft_putchar(' ');
	ft_putstr(str);
	ft_putchar('\n');
	sem_post(philo->mutex);
	return (1);
}

void	*loop_check(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	while (1)
		if (compare_time(philo->ttd))
			exit(1);
	return (NULL);
}
