/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:15:58 by hadufer           #+#    #+#             */
/*   Updated: 2022/03/12 10:05:32 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void	actual_time_if(t_philo *ph)
{
	sem_wait(ph->conf->actual_time_s);
	if (ph->time_begin_eat + ph->conf->time_to_die <= actual_time())
	{
		sem_post(ph->conf->actual_time_s);
		sem_wait(ph->conf->death_s);
		sem_wait(ph->conf->stop_print_s);
		ph->conf->stop_print = 1;
		sem_post(ph->conf->stop_print_s);
		sem_wait(ph->conf->writer_s);
		sem_wait(ph->conf->actual_time_s);
		printf("%ld %d died\n", actual_time()
			- ph->conf->start_time_ms, ph->ph_id);
		sem_post(ph->conf->actual_time_s);
		sem_post(ph->conf->game_over_s);
		pthread_detach(*ph->thread_watcher);
		pthread_detach(*ph->thread_id);
	}
	else
		sem_post(ph->conf->actual_time_s);
}

void	*routine_watcher(void *conf_ph)
{
	t_philo	*ph;

	ph = (t_philo *)conf_ph;
	while (1)
	{
		sem_wait(ph->eat_time_s);
		if (ph->conf->need_to_eat && (ph->eat_time >= ph->conf->need_to_eat))
		{
			sem_post(ph->eat_time_s);
			pthread_detach(*ph->thread_id);
			pthread_detach(*ph->thread_watcher);
			break ;
		}
		sem_post(ph->eat_time_s);
		actual_time_if(ph);
	}
	return (NULL);
}

void	*eat_time_watcher(void *v_conf)
{
	t_config	*conf;

	conf = (t_config *)v_conf;
	while (1)
	{
		sem_wait(conf->ph_already_eat_s);
		if (conf->ph_already_eat == conf->number_of_philosophers)
		{
			sem_post(conf->ph_already_eat_s);
			break ;
		}
		sem_post(conf->ph_already_eat_s);
	}
	printf("%d philosophers eated %d time(s)\n",
		conf->number_of_philosophers, conf->need_to_eat);
	sem_post(conf->game_over_s);
	return (NULL);
}

void	launch_thread(t_config *conf)
{
	int	i;

	i = 0;
	if (conf->need_to_eat)
	{
		pthread_create(&conf->eat_time_watcher,
			NULL, eat_time_watcher, (void *)(conf));
		pthread_detach(conf->eat_time_watcher);
	}
	while (i < conf->number_of_philosophers)
	{
		pthread_create((conf->ph + i)->thread_id,
			NULL, routine, (void *)(conf->ph + i));
		pthread_detach(*((conf->ph + i)->thread_id));
		i++;
	}
}
