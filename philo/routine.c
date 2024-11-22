/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:47:19 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/11/09 18:19:45 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	if (philo->table->dead)
	{
		printf("%zu philo %d is sleeping\n", gettime()
			- philo->table->start_time, philo->id);
		ft_usleep(philo->table->t_sleep, philo);
	}
}

void	start_eat(t_philo *philo)
{
	if (philo->table->dead)
	{
		philo->t_last_eat = gettime();
		philo->meal_eat++;
		printf("%zu philo %d is eating\n", gettime() - philo->table->start_time,
			philo->id);
		ft_usleep(philo->table->t_eat, philo);
		philo->t_last_eat = gettime();
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->l_fork);
		printf("%zu philo %d has taken first fork\n", gettime()
			- philo->table->start_time, philo->id);
		pthread_mutex_lock(philo->r_fork);
		printf("%zu philo %d has taken second fork\n", gettime()
			- philo->table->start_time, philo->id);
		start_eat(philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		printf("%zu philo %d has taken first fork\n", gettime()
			- philo->table->start_time, philo->id);
		pthread_mutex_lock(&philo->l_fork);
		printf("%zu philo %d has taken second fork\n", gettime()
			- philo->table->start_time, philo->id);
		start_eat(philo);
	}
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (1)
	{
		if (!philo->table->dead)
			break ;
		if (philo->meal_eat == philo->table->n_meal)
		{
			philo->table->finish++;
			break ;
		}
		take_fork(philo);
		sleeping(philo);
		if (philo->table->dead)
			printf("%zu philo %d is thinking\n", gettime()
				- philo->table->start_time, philo->id);
	}
    if (philo->table->finish == philo->table->n_meal)
        printf("%zu all philo have eaten\n", gettime()
				- philo->table->start_time);
	return (0);
}
