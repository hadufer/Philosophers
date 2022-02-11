/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:24:38 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/06 13:06:59 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#define ERR_ARG "Bad argument \n"
#define ERR_INIT "Error while initing t_config struct\n"

#include <pthread.h>

typedef struct s_config t_config;

typedef struct s_philo
{
	int	fork; // number of fork actually in possession of the philo
	int	l_f;
	int	*r_f;
	int	ph_id; // the id of the philo
	t_config	*conf;	// pointer to conf
	pthread_t	*thread_id; // actual thread
	pthread_mutex_t	*r_f_m; // mutex protect right fork
	pthread_mutex_t	l_f_m; // mutex protext left fork
}	t_philo;

typedef struct s_config {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	long int	start_time_ms;
	t_philo	*ph; // philo tab
	pthread_mutex_t	writer_m; // mutex
}	t_config;

int		check_args(int argc, char **argv);
int		init_conf_args(int argc, char **argv, t_config *conf);
void	init_conf_ph(t_config *conf);

// UTILS
long int	actual_time(void);
void		ft_usleep(int ms);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
#endif