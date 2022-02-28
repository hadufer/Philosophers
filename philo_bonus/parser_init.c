/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 07:06:03 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/28 19:34:45 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/semaphore.h>
#include <stdio.h>

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

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] && (i < argc))
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_conf_args(int argc, char **argv, t_config *conf)
{
	conf->num_ph = ft_atoi(argv[1]);
	conf->time_to_die = ft_atoi(argv[2]);
	conf->time_to_eat = ft_atoi(argv[3]);
	conf->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		conf->need_to_eat = ft_atoi(argv[5]);
	else
		conf->need_to_eat = 0;
	conf->ph_already_eat = 0;
	conf->start_time_ms = actual_time();
	conf->stop_print = 0;
	conf->ph = malloc(sizeof(t_philo) * conf->num_ph);
	sem_unlink("death_s");
	conf->death_s = sem_open("death_s", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("writer_s");
	conf->writer_s = sem_open("writer_s", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("game_over_s");
	conf->game_over_s = sem_open("game_over_s", O_CREAT | O_EXCL, 0644, 0);
	sem_unlink("fork_bowl");
	conf->f_bowl = sem_open("fork_bowl", O_CREAT | O_EXCL, 0644, conf->num_ph);
	if (argc == 6)
		conf->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		conf->number_of_times_each_philosopher_must_eat = -1;
	return (1);
}

void	init_conf_ph(t_config *conf)
{
	int	i;

	i = 0;
	while (i < conf->num_ph)
	{
		(conf->ph + i)->conf = conf;
		(conf->ph + i)->ph_id = i + 1;
		(conf->ph + i)->eat_time = 0;
		(conf->ph + i)->thread_id = malloc(sizeof(pthread_t));
		(conf->ph + i)->time_begin_eat = conf->start_time_ms;
		i++;
	}
}
