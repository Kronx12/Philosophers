/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@42lyon.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:10:24 by gbaud             #+#    #+#             */
/*   Updated: 2020/12/13 04:46:19 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/global.h"

int		init_parameters(int ac, char **av, t_simulation *simulation)
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
	return (0);
}

void	check_life(t_simulation *simulation)
{
	int i;
	int j;

	while (1)
	{
		i = -1;
		j = 0;
		while (++i < simulation->nop)
		{
			if (!simulation->philo[i].eat)
				j++;
			if (simulation->philo[i].eat && simulation->philo[i].ttd >= 0 &&
				compare_time(simulation->philo[i].ttd))
			{
				log_died(simulation, i);
				clean_exit(simulation);
			}
		}
		if (j == simulation->nop)
		{
			log_end(simulation);
			clean_exit(simulation);
		}
	}
}

void	setup_loop(t_simulation *simulation)
{
	int	i;

	i = -1;
	while (++i < simulation->nop)
	{
		simulation->philo[i].id = i;
		simulation->philo[i].ttd = get_time_ms() + simulation->ttd;
		simulation->philo[i].eat = simulation->max;
		simulation->philo[i].mutex = simulation->mutex;
		simulation->philo[i].mutex_lock = simulation->mutex_lock;
		simulation->philo[i].fork = simulation->fork;
		simulation->philo[i].nop = simulation->nop;
		simulation->philo[i].ittd = simulation->ttd;
		simulation->philo[i].itte = simulation->tte;
		simulation->philo[i].itts = simulation->tts;
		pthread_create(&simulation->philo[i].thread, NULL, run,
						&simulation->philo[i]);
		pthread_detach(simulation->philo[i].thread);
		pthread_join(simulation->philo[i].thread, NULL);
		
	}
}

int		main(int ac, char **av)
{
	t_simulation	simulation;

	init_parameters(ac, av, &simulation);
	printf_parameters(simulation);
	sem_unlink("/sem-mutex");
	if ((simulation.mutex =
		sem_open("/sem-mutex", O_CREAT, 0660, 1)) == SEM_FAILED)
		error("Erreur de semaphore", ALLOCATION);
	sem_unlink("/sem-mutexlock");
	if ((simulation.mutex_lock =
		sem_open("/sem-mutexlock", O_CREAT, 0660, 1)) == SEM_FAILED)
		error("Erreur de semaphore", ALLOCATION);
	sem_unlink("/sem-fork");
	if ((simulation.fork =
		sem_open("/sem-fork", O_CREAT, 0660, simulation.nop)) == SEM_FAILED)
		error("Erreur de semaphore", ALLOCATION);
	setup_loop(&simulation);
	check_life(&simulation);
	return (0);
}
