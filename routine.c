/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:14:59 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/11 17:52:32 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	*routine(void *conf_ph)
{
	t_philo	*ph;

	ph = (t_philo *)conf_ph;
	pthread_mutex_lock(&ph->l_f);
	pthread_mutex_lock(ph->r_f);
	pthread_mutex_lock(&ph->conf->writer_m);
	printf("%ld %d has taken a fork\n", actual_time() - ph->conf->start_time_ms, ph->ph_id);
	printf("%ld %d is eating\n", actual_time() - ph->conf->start_time_ms, ph->ph_id);
	pthread_mutex_unlock(&ph->conf->writer_m);
	ft_usleep(ph->conf->time_to_eat);
	pthread_mutex_unlock(&ph->l_f);
	pthread_mutex_unlock(ph->r_f);
	pthread_mutex_lock(&ph->conf->writer_m);
	printf("%ld %d has taken a fork\n", actual_time() - ph->conf->start_time_ms, ph->ph_id);
	return NULL;
}