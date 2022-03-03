/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:15:58 by hadufer           #+#    #+#             */
/*   Updated: 2022/03/03 19:04:06 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void	actual_time_if(t_philo *ph)
{
	if (ph->time_begin_eat + ph->conf->time_to_die <= actual_time())
	{
		pthread_mutex_unlock(&ph->conf->actual_time_m);
		pthread_mutex_lock(&ph->conf->death_m);
		pthread_mutex_lock(&ph->conf->stop_print_m);
		ph->conf->stop_print = 1;
		pthread_mutex_unlock(&ph->conf->stop_print_m);
		pthread_mutex_lock(&ph->conf->writer_m);
		printf("%ld %d died\n", actual_time()
			- ph->conf->start_time_ms, ph->ph_id);
		pthread_mutex_unlock(&ph->conf->game_over_m);
		pthread_detach(*ph->thread_watcher);
		pthread_detach(*ph->thread_id);
	}
}

void	*routine_watcher(void *conf_ph)
{
	t_philo	*ph;

	ph = (t_philo *)conf_ph;
	while (1)
	{
		pthread_mutex_lock(&ph->eat_time_m);
		if (ph->conf->need_to_eat && (ph->eat_time >= ph->conf->need_to_eat))
		{
			pthread_mutex_unlock(&ph->eat_time_m);
			pthread_detach(*ph->thread_id);
			pthread_detach(*ph->thread_watcher);
			break ;
		}
		pthread_mutex_unlock(&ph->eat_time_m);
		pthread_mutex_lock(&ph->conf->actual_time_m);
		actual_time_if(ph);
		pthread_mutex_unlock(&ph->conf->actual_time_m);
	}
	return (NULL);
}

void	*eat_time_watcher(void *v_conf)
{
	t_config	*conf;

	conf = (t_config *)v_conf;
	while (1)
	{
		pthread_mutex_lock(&conf->ph_already_eat_m);
		if (conf->ph_already_eat == conf->number_of_philosophers)
		{
			pthread_mutex_unlock(&conf->ph_already_eat_m);
			break ;
		}
		pthread_mutex_unlock(&conf->ph_already_eat_m);
	}
	printf("%d philosophers eated %d time(s)\n",
		conf->number_of_philosophers, conf->need_to_eat);
	pthread_mutex_unlock(&conf->game_over_m);
	return (NULL);
}

void	launch_thread(t_config *conf)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&conf->game_over_m);
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
