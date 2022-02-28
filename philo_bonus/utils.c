/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 07:09:08 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/28 18:08:51 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	putstr_ph(char *str, t_philo *ph)
{
	sem_wait(ph->conf->writer_s);
	if (!ph->conf->stop_print)
		printf("%ld %d %s\n",
			actual_time() - ph->conf->start_time_ms, ph->ph_id, str);
	sem_post(ph->conf->writer_s);
}
