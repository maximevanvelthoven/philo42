/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:16:39 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/11/09 18:33:44 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_table *table, int i)
{
    while (1)
    {
        i = 0;
        while (i < table->nbr_philo)
        {
            if (table->finish == table->nbr_philo)
                break;
            if (gettime() - table->philo[i].t_last_eat > table->t_die)
            {
                table->dead = 0;
                printf("%zu philo %d is dead\n", gettime() - table->start_time, table->philo[i].id);
                break;
            }
            i++;
        }
        if (table->dead == 0 || table->finish == table->nbr_philo)
            break;
    }
}

int	start_thread(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = gettime();
	while (i < table->nbr_philo)
	{
		table->philo[i].t_last_eat = table->start_time;
		if (pthread_create(&table->philo[i].thread, NULL, &routine,
				&table->philo[i]))
			return (1);
		i++;
	}
	monitor(table, 0);
	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	return (0);
}
