/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 07:06:03 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/06 13:06:49 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

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
	conf->number_of_philosophers = ft_atoi(argv[1]);
	conf->time_to_die = ft_atoi(argv[2]);
	conf->time_to_eat = ft_atoi(argv[3]);
	conf->time_to_sleep = ft_atoi(argv[4]);
	conf->ph = malloc(sizeof(t_philo) * conf->number_of_philosophers);
	if (pthread_mutex_init(&conf->writer_m, NULL) != 0)
		return (0);
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
	while (i < conf->number_of_philosophers)
	{
		(conf->ph + i)->conf = conf;
		(conf->ph + i)->ph_id = i;
		(conf->ph + i)->thread_id = malloc(sizeof(pthread_t));
		(conf->ph + i)->l_f = 1;
		pthread_mutex_init(&(conf->ph + i)->l_f_m, NULL);
		if (i == (conf->number_of_philosophers - 1))
			(conf->ph + i)->r_f = &conf->ph->l_f;
		else
			(conf->ph + i)->r_f = &(conf->ph + i + 1)->l_f;
		i++;
	}
}
