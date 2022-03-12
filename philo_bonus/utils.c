/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 07:09:08 by hadufer           #+#    #+#             */
/*   Updated: 2022/03/12 10:15:42 by hadufer          ###   ########.fr       */
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
	sem_wait(ph->conf->stop_print_s);
	if (!ph->conf->stop_print)
	{
		sem_wait(ph->conf->actual_time_s);
		printf("%ld %d %s\n",
			actual_time() - ph->conf->start_time_ms, ph->ph_id, str);
		sem_post(ph->conf->actual_time_s);
	}
	sem_post(ph->conf->stop_print_s);
	sem_post(ph->conf->writer_s);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
	{
		return (1 << 10);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	sum;

	sum = 0;
	i = -1;
	while (str[++i])
		sum = (sum * 10) + (str[i] - 48);
	return (sum);
}
