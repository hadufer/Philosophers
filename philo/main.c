/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:24:42 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/28 17:30:06 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_config	conf;

	if (argc != 5 && argc != 6)
		ft_putstr_fd(ERR_ARG, 1);
	else if (!check_args(argc, argv))
		ft_putstr_fd(ERR_ARG, 1);
	else if (!init_conf_args(argc, argv, &conf))
		ft_putstr_fd(ERR_ARG, 1);
	else if (ft_atoi(argv[1]) == 0)
		ft_putstr_fd(ERR_ARG, 1);
	else
	{
		init_conf_ph(&conf);
		launch_thread(&conf);
		pthread_mutex_lock(&conf.game_over_m);
	}
}
