/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:14:59 by hadufer           #+#    #+#             */
/*   Updated: 2022/03/03 18:57:28 by hadufer          ###   ########.fr       */
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
	pthread_mutex_lock(&ph->conf->actual_time_m);
	ph->time_begin_eat = actual_time();
	pthread_mutex_unlock(&ph->conf->actual_time_m);
	ft_usleep(ph->conf->time_to_eat);
	pthread_mutex_lock(&ph->eat_time_m);
	ph->eat_time += 1;
	pthread_mutex_unlock(&ph->eat_time_m);
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
	t_philo		*ph;
	pthread_t	watch;

	ph = (t_philo *)conf_ph;
	if ((ph->ph_id % 2) == 0)
		ft_usleep(ph->conf->time_to_eat / 10);
	ph->thread_watcher = &watch;
	pthread_create(&watch, NULL, routine_watcher, (void *)(ph));
	while (1)
	{
		if (ph->conf->need_to_eat && (ph->eat_time == ph->conf->need_to_eat))
		{
			pthread_mutex_lock(&ph->conf->ph_already_eat_m);
			ph->conf->ph_already_eat += 1;
			pthread_mutex_unlock(&ph->conf->ph_already_eat_m);
			break ;
		}
		eat(ph);
		sleep_think(ph);
	}
	return (NULL);
}
