/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:04:22 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/11/09 18:41:07 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_T
# define PHILO_T

# include "stdio.h"
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_table
{
	int					dead;
	int					finish;
	int					nbr_philo;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				n_meal;
	long				start_time;
	t_philo				*philo;
	// rajouter mutex pour dead, pour finish, et pour l_last_meal;
}						t_table;

typedef struct s_philo
{
	t_table				*table;
	int					id;
	long				meal_eat;
	long				t_last_eat;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			thread;
}						t_philo;

// check des arguments + initialisations de la table/philo

int						ft_parsing(int ac, char **av);
int						init_struct(t_table *table, int ac, char **av);

// lancements des threads && surveillance

int						start_thread(t_table *table);
void					monitor(t_table *table, int i);

// execution routine

void					*routine(void *void_philo);

// utils

long					gettime(void);
void					ft_usleep(long time, t_philo *philo);

#endif