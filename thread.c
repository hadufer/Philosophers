/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:15:58 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/16 14:52:12 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	*routine_watcher(void *conf_ph)
{
	t_philo	*ph;

	ph = (t_philo *)conf_ph;
	while (1)
	{
		if (ph->time_begin_eat + ph->conf->time_to_die <= actual_time())
		{
			ph->conf->stop_print = 1;
			pthread_mutex_lock(&ph->conf->death_m);
			printf("%ld %d died\n", actual_time() - ph->conf->start_time_ms, ph->ph_id);
			pthread_mutex_unlock(&ph->conf->game_over_m);
			return (NULL);
		}
	}
	// Unlock mutex game_over
	return (NULL);
}

void	launch_thread(t_config *conf)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&conf->game_over_m);
	while (i < conf->number_of_philosophers)
	{
		pthread_create((conf->ph + i)->thread_id, NULL, routine, (void *)(conf->ph + i));
		pthread_detach(*((conf->ph + i)->thread_id));
		i++;
	}
}