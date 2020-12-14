/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@42lyon.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:10:24 by gbaud             #+#    #+#             */
/*   Updated: 2020/12/14 06:30:33 by gbaud            ###   ########lyon.fr   */
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
	if (!(simulation->pid = malloc(sizeof(pid_t) * simulation->nop)))
		error("Malloc error", ALLOCATION);
	return (0);
}

void	check_life(t_simulation *simulation)
{
	int		i;
	int		status;
	pid_t	tmp_pid;

	status = 0;
	tmp_pid = -1;
	while (!status && tmp_pid <= 0)
		tmp_pid = waitpid(-1, &status, 0);
	if (WEXITSTATUS(status))
	{
		i = -1;
		while (++i < simulation->nop)
			if (tmp_pid != simulation->pid[i])
				kill(simulation->pid[i], SIGKILL);
			else
				log_died(simulation, simulation->philo[i].id);
	}
	else
		log_end(simulation);
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
		simulation->pid[i] = fork();
		if (!simulation->pid[i])
			run(&simulation->philo[i]);
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
	clean_exit(&simulation);
	return (0);
}
