/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:24:38 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/16 14:51:32 by hadufer          ###   ########.fr       */
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
	int	ph_id; // the id of the philo
	long int time_begin_eat; // the time when ph beginned to eat
	t_config	*conf;	// pointer to conf
	pthread_t	*thread_id; // actual thread
	pthread_mutex_t	*r_f; // mutex protect right fork
	pthread_mutex_t	l_f; // mutex protext left fork
}	t_philo;

typedef struct s_config {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	long int	start_time_ms;
	int	stop_print;	// Dont print if the program need to stop
	t_philo	*ph; // philo tab
	pthread_mutex_t	writer_m; // mutex
	pthread_mutex_t	game_over_m; // mutex game over
	pthread_mutex_t	death_m; // mutex game over
}	t_config;

int		check_args(int argc, char **argv);
int		init_conf_args(int argc, char **argv, t_config *conf);
void	init_conf_ph(t_config *conf);
void	launch_thread(t_config *conf);
void	*routine(void *conf_ph);
void	*routine_watcher(void *conf_ph);

// UTILS
long int	actual_time(void);
void		ft_usleep(int ms);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		putstr_ph(char *str, t_philo *ph);
#endif
