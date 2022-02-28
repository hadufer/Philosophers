/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:14:59 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/28 19:34:41 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	eat(t_philo *ph)
{
	sem_wait(ph->conf->f_bowl);
	putstr_ph("has taken a fork", ph);
	sem_wait(ph->conf->f_bowl);
	putstr_ph("has taken a fork", ph);
	putstr_ph("is eating", ph);
	ph->time_begin_eat = actual_time();
	ft_usleep(ph->conf->time_to_eat);
	ph->eat_time += 1;
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
	pthread_create(&watch, NULL, routine_watcher, (void *)(ph));
	pthread_detach(watch);
	while (1)
	{
		if (ph->conf->need_to_eat && (ph->eat_time == ph->conf->need_to_eat))
		{
			ph->conf->ph_already_eat += 1;
			break ;
		}
		eat(ph);
		sleep_think(ph);
	}
	return (NULL);
}
