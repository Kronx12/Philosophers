/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@42lyon.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:16:43 by gbaud             #+#    #+#             */
/*   Updated: 2020/12/13 04:46:10 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/global.h"

long	ft_atoi(char *str)
{
	int		i;
	long	res;
	t_bool	b;

	i = -1;
	res = 0;
	b = FALSE;
	if (str[0] == '-' && i++)
		b = TRUE;
	while (str[++i])
		res = res * 10 + (str[i] - '0');
	if (b)
		res *= -1;
	return (res);
}

void	ft_putnbr(long nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		ft_putnbr(nb * -1);
	}
	else if (nb <= 9)
		ft_putchar('0' + nb);
	else
	{
		ft_putnbr(nb / 10);
		ft_putchar('0' + nb % 10);
	}
}

void	ft_putstr(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		ft_putchar(str[i]);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

t_bool	allisdigit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		str++;
	}
	return (TRUE);
}
