/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:25:59 by gbaud             #+#    #+#             */
/*   Updated: 2020/11/25 02:33:32 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/global.h"

void log_died(int i)
{
    ft_putstr("\033[1;31m");
    ft_putnbr(get_time_ms());
    ft_putchar(' ');
    ft_putnbr(i + 1);
    ft_putstr(" died\n");
    ft_putstr("\033[1;30m");
}