/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@42lyon.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 08:43:17 by gbaud             #+#    #+#             */
/*   Updated: 2020/12/14 06:27:07 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/global.h"

long	get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((clock_t)tv.tv_sec * 1000 + (clock_t)tv.tv_usec / 1000);
}

int		compare_time(long time)
{
	if (time == -1)
		return (0);
	return (time < get_time_ms());
}
