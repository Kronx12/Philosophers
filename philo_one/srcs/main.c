/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:10:24 by gbaud             #+#    #+#             */
/*   Updated: 2020/11/25 02:37:06 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/global.h"

int init_parameters(int ac, char **av, t_simulation *simulation)
{
	int i;

	i = 0;
	if (ac < 5 || ac > 6)
		error("Not valid parameters count", ARGUMENT);
	while (++i < ac)
	    if (!allisdigit(av[i]))
	        error("Parameters must be numbers", ARGUMENT);
	simulation->nop = ft_atoi(av[1]);
	simulation->ttd = ft_atoi(av[2]);
	simulation->tte = ft_atoi(av[3]);
	simulation->tts = ft_atoi(av[4]);
	simulation->max = -1;
	if (ac == 6)
		simulation->max = ft_atoi(av[5]);
	simulation->start = get_time_ms();
	if (!(simulation->philo = malloc(sizeof(t_philo) * simulation->nop)))
		error("Malloc error", ALLOCATION);
	if (!(simulation->fork = malloc(sizeof(pthread_mutex_t) * simulation->nop)))
		error("Malloc error", ALLOCATION);
	return (0);
}

void	check_life(t_simulation *simulation)
{
	int i;

	while (1)
	{
		i = -1;
		while (++i < simulation->nop)
			if (compare_time(simulation->philo[i].ttd))
			{
				i = -1;
				while (++i < simulation->nop)
					pthread_kill(simulation->philo[i].thread, 0);
				log_died(i);
			}
	}
}

int main(int ac, char **av)
{
	int i;
	t_simulation simulation;

	init_parameters(ac, av, &simulation);
	printf_parameters(simulation);
	if (pthread_mutex_init(&simulation.mutex, NULL))
        error("Erreur de mutex", ALLOCATION);
    if (pthread_mutex_init(&simulation.mutex_lock, NULL))
        error("Erreur de mutex", ALLOCATION);	
	i = -1;
	while (++i < simulation.nop)
	{
		simulation.philo[i].id = i;
		simulation.philo[i].ttd = simulation.ttd;
		simulation.philo[i].eat = simulation.max;
		if (pthread_mutex_init(&simulation.fork[i], NULL))
			error("Erreur de mutex", ALLOCATION);
		pthread_create(&simulation.philo[i].thread, NULL, run, &simulation.philo[i]);
		pthread_detach(simulation.philo[i].thread);
		pthread_join(simulation.philo[i].thread, NULL);
	}
	check_life(&simulation);
	return (0);
}
