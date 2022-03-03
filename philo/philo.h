/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:24:38 by hadufer           #+#    #+#             */
/*   Updated: 2022/03/03 18:55:17 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERR_ARG "Bad argument \n"
# define ERR_INIT "Error while initing t_config struct\n"

# include	<pthread.h>

typedef struct s_config	t_config;

typedef struct s_philo
{
	int				ph_id;
	int				eat_time;
	long int		time_begin_eat;
	t_config		*conf;
	pthread_t		*thread_id;
	pthread_t		*thread_watcher;
	pthread_mutex_t	*r_f;
	pthread_mutex_t	l_f;
	pthread_mutex_t	eat_time_m;
}	t_philo;

typedef struct s_config {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				need_to_eat;
	int				ph_already_eat;
	int				number_of_times_each_philosopher_must_eat;
	long int		start_time_ms;
	int				stop_print;
	t_philo			*ph;
	pthread_mutex_t	writer_m;
	pthread_mutex_t	game_over_m;
	pthread_mutex_t	death_m;
	pthread_mutex_t	actual_time_m;
	pthread_mutex_t	stop_print_m;
	pthread_mutex_t	ph_already_eat_m;
	pthread_t		eat_time_watcher;
}	t_config;

int			check_args(int argc, char **argv);
int			init_conf_args(int argc, char **argv, t_config *conf);
void		init_conf_ph(t_config *conf);
void		launch_thread(t_config *conf);
void		*routine(void *conf_ph);
void		*routine_watcher(void *conf_ph);

// UTILS
long int	actual_time(void);
void		ft_usleep(int ms);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		putstr_ph(char *str, t_philo *ph);
#endif
