/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:41:03 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/11/09 18:40:15 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long time, t_philo *philo)
{
	long	time_now;

	time_now = gettime();
	while (philo->table->dead && gettime() - time_now < time)
		usleep(200);
}
// rajouter check_dead check_finish