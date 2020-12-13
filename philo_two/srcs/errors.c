/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@42lyon.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:46:48 by gbaud             #+#    #+#             */
/*   Updated: 2020/12/13 04:46:28 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/global.h"

int		error(char *err, t_error type)
{
	ft_putstr("\033[1;36m[PHILO_ONE]: ");
	if (type == ARGUMENT)
		ft_putstr("\033[1;31mArguments error: \033[0;33m");
	else if (type == ALLOCATION)
		ft_putstr("\033[1;31mAllocation error: \033[0;33m");
	else if (type == DIED)
		ft_putstr("\033[1;31mPhilosopher is dead: \033[0;33m");
	ft_putstr(err);
	ft_putstr("\n\033[0;0m");
	exit(EXIT_FAILURE);
	return (1);
}

void	printf_parameters(t_simulation simulation)
{
	ft_putstr("\n\n\033[1;33m==============================\n\033[0m");
	ft_putstr("\033[1;32mNumber of philosophes: \033[1;36m");
	ft_putnbr(simulation.nop);
	ft_putstr("\033[0m\n");
	ft_putstr("\033[1;32mTime to die: \033[1;36m");
	ft_putnbr(simulation.ttd);
	ft_putstr("ms\033[0m\n");
	ft_putstr("\033[1;32mTime to eat: \033[1;36m");
	ft_putnbr(simulation.tte);
	ft_putstr("ms\033[0m\n");
	ft_putstr("\033[1;32mTime to sleep: \033[1;36m");
	ft_putnbr(simulation.tts);
	ft_putstr("ms\033[0m\n");
	ft_putstr("\033[1;32mMax eat: \033[1;36m");
	ft_putnbr(simulation.max);
	ft_putstr("\033[0m\n");
	ft_putstr("\033[1;33m==============================\n\n\n\033[0m");
}

void	clean_exit(t_simulation *simulation)
{
	sem_close(simulation->mutex);
	sem_close(simulation->mutex_lock);
	sem_close(simulation->fork);
	free(simulation->philo);
	exit(EXIT_SUCCESS);
}
