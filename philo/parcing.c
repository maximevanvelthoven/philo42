/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:10:14 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/11/05 17:12:32 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
        i++;
	}
	return (0);
}

int	ft_parsing(int ac, char **av)
{
	int		i;

	i = 1;
	if (av[1][0] == '0' && av[1][1] == '\0')
	{
		printf("minimun 1 philosopher\n");
		return (1);
	}
	while (i < ac)
	{
		if (is_num(av[i]))
		{
			printf("argument non valide uniquement chiffre\n");
			return (1);
		}
		i++;
	}
	return (0);
}
