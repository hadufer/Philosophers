/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:15:58 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/15 19:01:58 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	*routine_watcher(void *conf_ph)
{
	t_philo	*ph;

	ph = (t_philo *)conf_ph;
	while (ph->time_begin_eat + ph->conf->time_to_die <= actual_time())
	{
		putstr_ph("died", ph);
		pthread_mutex_unlock(&ph->conf->game_over_m);
	}
	// Unlock mutex game_over
}

void	*begin_routine(void	*conf_ph)
{
	t_philo	*ph;

	ph = (t_philo *)conf_ph;
	if ((ph->ph_id % 2) == 0)
		ft_usleep(ph->conf->time_to_eat / 100);
	// lock to prevent the main thread from returning
	pthread_create(ph->thread_id, NULL, routine, (void *)(ph));
	return (NULL);
}

void	launch_thread(t_config *conf)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&conf->game_over_m);
	while (i < conf->number_of_philosophers)
	{
		pthread_create((conf->ph + i)->thread_id, NULL, begin_routine, (void *)(conf->ph + i));
		i++;
	}
}