/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:14:59 by hadufer           #+#    #+#             */
/*   Updated: 2022/03/12 09:53:32 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	eat(t_philo *ph)
{
	sem_wait(ph->conf->f_bowl);
	putstr_ph("has taken a fork", ph);
	sem_wait(ph->conf->f_bowl);
	putstr_ph("has taken a fork", ph);
	putstr_ph("is eating", ph);
	sem_wait(ph->conf->actual_time_s);
	ph->time_begin_eat = actual_time();
	sem_post(ph->conf->actual_time_s);
	ft_usleep(ph->conf->time_to_eat);
	sem_wait(ph->eat_time_s);
	ph->eat_time += 1;
	sem_post(ph->eat_time_s);
}

void	sleep_think(t_philo *ph)
{
	sem_post(ph->conf->f_bowl);
	sem_post(ph->conf->f_bowl);
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
			sem_wait(ph->conf->ph_already_eat_s);
			ph->conf->ph_already_eat += 1;
			sem_post(ph->conf->ph_already_eat_s);
			break ;
		}
		eat(ph);
		sleep_think(ph);
	}
	return (NULL);
}
