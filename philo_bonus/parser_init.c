/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 07:06:03 by hadufer           #+#    #+#             */
/*   Updated: 2022/03/12 10:23:20 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/semaphore.h>

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

static char	*ft_strconcat_dup(char *str1, char *str2)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	while (str1[i])
	{
		ret[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		ret[i + j] = str2[j];
		j++;
	}
	ret[i + j] = 0;
	return (ret);
}

static void	init_sem(t_config *conf)
{
	sem_unlink("death_s");
	conf->death_s = sem_open("death_s", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("writer_s");
	conf->writer_s = sem_open("writer_s", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("game_over_s");
	conf->game_over_s = sem_open("game_over_s", O_CREAT | O_EXCL, 0644, 0);
	sem_unlink("fork_bowl");
	conf->f_bowl = sem_open("fork_bowl", O_CREAT | O_EXCL,
			0644, conf->number_of_philosophers);
	sem_unlink("actual_time_s");
	conf->actual_time_s = sem_open("actual_time_s", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("stop_print_s1");
	conf->stop_print_s = sem_open("stop_print_s1", O_CREAT | O_EXCL, 0644, 1);
}

int	init_conf_args(int argc, char **argv, t_config *conf)
{
	conf->number_of_philosophers = ft_atoi(argv[1]);
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
	conf->ph = malloc(sizeof(t_philo) * conf->number_of_philosophers);
	init_sem(conf);
	if (argc == 6)
		conf->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		conf->number_of_times_each_philosopher_must_eat = -1;
	return (1);
}

void	init_conf_ph(t_config *conf)
{
	int		i;
	char	*tmp;
	char	*itoa_i;

	i = 0;
	while (i < conf->number_of_philosophers)
	{
		(conf->ph + i)->conf = conf;
		(conf->ph + i)->ph_id = i + 1;
		(conf->ph + i)->eat_time = 0;
		(conf->ph + i)->thread_id = malloc(sizeof(pthread_t));
		(conf->ph + i)->time_begin_eat = conf->start_time_ms;
		(conf->ph + i)->thread_watcher = NULL;
		itoa_i = ft_itoa(i);
		tmp = ft_strconcat_dup("eat_time_s", itoa_i);
		sem_unlink(tmp);
		(conf->ph + i)->eat_time_s = sem_open(tmp, O_CREAT | O_EXCL, 0644, 1);
		free(tmp);
		free(itoa_i);
		i++;
	}
}
