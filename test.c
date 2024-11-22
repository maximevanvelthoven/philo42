/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:44:36 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/10/24 16:47:15 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

int	common = 162;
pthread_mutex_t	mutex;

typedef struct s_context
{
	unsigned long 	time_start;
	unsigned int	nb_of_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned int	nb_of_meals;
	//bool			isdead;
}	t_context;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	myfork;
	pthread_mutex_t	*neigh_fork;
	pthread_t		thread;
	t_context		*context;
    bool			isdead; // verifier si a mettre dans philo ou bien context    
}	t_philo;

void	*threadfun(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *) void_philo;
	while (true)//not dead or full all
	{
		if (philo->id % 2)
		{
			pthread_mutex_lock(&(philo->myfork)); // gets own fork
			pthread_mutex_lock((philo->neigh_fork)); // gets neighbours fork
		}
		else
			pthread_mutex_lock((philo->neigh_fork)); // gets neighbours fork
			pthread_mutex_lock(&(philo->myfork)); // gets own fork
		fn_eating();
		if (philo->id % 2)
		{
			pthread_mutex_unlock(&(philo->myfork)); // gets own fork
			pthread_mutex_unlock((philo->neigh_fork)); // gets neighbours fork
		}
		else
			pthread_mutex_unlock((philo->neigh_fork)); // gets neighbours fork
			pthread_mutex_unlock(&(philo->myfork)); // gets own fork
		fn_sleep();
		fn_thinking();
	}
}

int	main(int argc, char **argv)
{
	long		t;
	int			nb_threads;
	int			rc;
	t_philo		*philo;
	t_context	context;

	// initialise context
	context.time_to_die= 800;
	context.time_to_eat = 800;
	context.time_to_sleep = 800;
	context.nb_of_meals = -1;

	
	nb_threads = 5;
	// malloc and init philo
	philo = malloc(sizeof(t_philo) * nb_threads);
	t = 0;
	while (t < nb_threads)
	{
		philo[t].id = t;
		pthread_mutex_init(&(philo[t].myfork), NULL);
		philo[t].neigh_fork = &(philo[(t + 1) % nb_threads].myfork);
		philo[t].context = &context;
		t++;
	}
	
	// create pthreads_t == start their routines
	t = 0;
	// get time of the day a mettre ici
	while (t < nb_threads) {
		pthread_create(&(philo[t].thread), NULL, threadfun, (void *) &philo[t]);
		t++;
	}

	/*
	*/
	// join threads
	t = 0;
	while (t < nb_threads) {
		pthread_join(philo[t].thread, NULL);
		t++;
	}

	//destroy mutexes
	t = 0;
	while (t < nb_threads)
	{
		pthread_mutex_destroy(&(philo[t].myfork));
		t++;
	}

	pthread_exit(NULL);
}

/* COMMENT
*/
	/*
	// malloc and init forks
	forks = malloc(sizeof(pthread_mutex_t) * (nb_of_philo));
	t = 0;
	while (t < nb_threads)
		pthread_mutex_init(&forks[t], NULL);
	*/