/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:14:59 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/16 12:20:06 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_f);
	putstr_ph("has taken a fork", ph);
	pthread_mutex_lock(ph->r_f);
	putstr_ph("has taken a fork", ph);
	putstr_ph("is eating", ph);
	ph->time_begin_eat = actual_time();
	ft_usleep(ph->conf->time_to_eat);
}

void	sleep_think(t_philo *ph)
{
	pthread_mutex_unlock(&ph->l_f);
	pthread_mutex_unlock(ph->r_f);
	putstr_ph("is sleeping", ph);
	ft_usleep(ph->conf->time_to_sleep);
	putstr_ph("is thinking", ph);
}

void	*routine(void *conf_ph)
{
	t_philo	*ph;
	pthread_t	watch;

	ph = (t_philo *)conf_ph;
	if ((ph->ph_id % 2) == 0)
		ft_usleep(ph->conf->time_to_eat / 100);
	pthread_create(&watch, NULL, routine_watcher, (void *)(ph));
	pthread_detach(watch);
	while (1)
	{
		eat(ph);
		sleep_think(ph);
	}
	return (NULL);
}