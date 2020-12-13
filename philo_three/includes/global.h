/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@42lyon.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:09:38 by gbaud             #+#    #+#             */
/*   Updated: 2020/12/13 04:46:15 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <semaphore.h>

typedef enum		e_error
{
	ARGUMENT,
	ALLOCATION,
	DIED
}					t_error;

typedef struct		s_philo
{
	pthread_t		thread;
	long			eat;
	long			ttd;
	long			ittd;
	long			itte;
	long			itts;
	int				id;
	int				nop;
	sem_t			*mutex;
	sem_t			*mutex_lock;
	sem_t			*fork;
}					t_philo;

typedef struct		s_simulation
{
	int				nop;
	int				now;
	long			ttd;
	long			tte;
	long			tts;
	long			max;
	long			start;
	sem_t			*mutex;
	sem_t			*mutex_lock;
	sem_t			*fork;
	t_philo			*philo;
}					t_simulation;

typedef int			t_bool;
# define TRUE		1
# define FALSE		0

/*
**  @brief Convert String to Number
**  @param char* in
**  @return Converted result
*/
long				ft_atoi(char *in);

/*
**  @brief Print str to standard output
**  @param char* str
**  @return None
*/
void				ft_putstr(char *str);

/*
**  @brief Print nb to standard output
**  @param long nb
**  @return None
*/
void				ft_putnbr(long nb);

/*
**  @brief Print c to standard output
**  @param char c
**  @return None
*/
void				ft_putchar(char c);

/*
**  @brief Check if string contain only digits
**  @param char *str
**  @return TRUE if all is digit
*/
t_bool				allisdigit(char *str);

/*
**  @brief Print err to standard output and exit failure
**  @param char err
**  @param t_error type
**  @return EXIT_FAILURE
*/
int					error(char *err, t_error type);

/*
**  @brief Free all semaphore
**  @param t_simulation simulation
**  @return EXIT_SUCCESS
*/
void				clean_exit(t_simulation *simulation);

/*
**  @brief Print all simulation to standard output
**  @param t_simulation simulation
**  @return None
*/
void				printf_parameters(t_simulation simulation);

/*
**  @brief Get current time in ms
**  @return Time in ms
*/
long				get_time_ms(void);

/*
**  @brief Compare time with current time
**  @param long time
**  @return 1 if time is passed
*/
int					compare_time(long time);

/*
**  @brief Run philosopher
**  @param void *p
**  @return NULL
*/
void				*run(void *p);

/*
**  @brief Log philosopher die
**  @param t_simulation *simulation
**  @param int i
**  @return None
*/
void				log_died(t_simulation *simulation, int i);

/*
**  @brief Log philosopher end
**  @param t_simulation *simulation
**  @return None
*/
void				log_end(t_simulation *simulation);

/*
**  @brief Log philosopher
**  @param t_philo *philo
**  @param char *str
**  @return None
*/
int					log_action(t_philo *philo, char *str);

#endif
