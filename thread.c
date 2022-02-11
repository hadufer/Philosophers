/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:15:58 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/11 18:13:48 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	launch_thread(t_config *conf)
{
	int	i;

	i = 0;
	pthread_t	ptest;
	while (i < conf->number_of_philosophers)
	{
		if ((i % 2) == 0)
			pthread_create((conf->ph + i)->thread_id, NULL, routine, (void *)(conf->ph + i));
		i++;
	}
	i = 0;
	while (i < conf->number_of_philosophers)
	{
		if ((i % 2) != 0)
			pthread_create((conf->ph + i)->thread_id, NULL, routine, (void *)(conf->ph + i));
		i++;
	}
}