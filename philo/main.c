/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:06:20 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/11/09 18:04:14 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
	{
		printf("pas le bon nombre d'argument\n");
		return (0);
	}
	if (ft_parsing(ac, av)) // rajouter dans parsing une regle si 1 philosopher
		return (1);
	if (init_struct(&table, ac, av))
		return (1);
	if (start_thread(&table))
		return (1);
	return (0);
}
