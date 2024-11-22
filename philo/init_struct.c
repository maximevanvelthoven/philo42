/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:40:54 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/11/09 18:31:35 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	i;
	long	result;
	long	final;

	i = 0;
	final = 0;
	result = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			result *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		// if (final > INT_MAX || final < INT_MIN)
		// 	return (LONG_MAX);
		final = final * 10 + (str[i] - 48);
		i++;
	}
	return (final * result);
}

int	init_table(t_table *table, int ac, char **av)
{
	table->dead = 1;
	table->finish = 1;
	table->start_time = 0;
	table->nbr_philo = ft_atol(av[1]);
	table->t_die = ft_atol(av[2]);
	table->t_eat = ft_atol(av[3]);
	table->t_sleep = ft_atol(av[4]);
	if (ac == 6)
		table->n_meal = ft_atol(av[5]);
	else
		table->n_meal = -1;
	return (0);
}
int	init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->nbr_philo);
	while (i < table->nbr_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meal_eat = 0;
		table->philo[i].t_last_eat = 0;
		if (pthread_mutex_init(&table->philo[i].l_fork, NULL))
			return (1);
		table->philo[i].r_fork = &table->philo[i + 1 % table->nbr_philo].l_fork;
		table->philo[i].table = table;
		i++;
	}
	return (0);
}

int	init_struct(t_table *table, int ac, char **av)
{
	if (init_table(table, ac, av))
	{
		printf("erreur initialisation mutex table\n");
		return (1);
	}
	if (init_philo(table))
	{
		printf("erreur initialisation mutex fork\n");
		// error handeling free si necessaire
		return (1);
	}
	return (0);
}