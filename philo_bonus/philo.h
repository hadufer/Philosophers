/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:24:38 by hadufer           #+#    #+#             */
/*   Updated: 2022/02/28 19:34:24 by hadufer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERR_ARG "Bad argument \n"
# define ERR_INIT "Error while initing t_config struct\n"

# include	<pthread.h>
# include <sys/semaphore.h>
# include <fcntl.h>

typedef struct s_config	t_config;

typedef struct s_philo
{
	int				ph_id;
	int				eat_time;
	long int		time_begin_eat;
	t_config		*conf;
	pthread_t		*thread_id;
}	t_philo;

typedef struct s_config {
	int				num_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				need_to_eat;
	int				ph_already_eat;
	int				number_of_times_each_philosopher_must_eat;
	long int		start_time_ms;
	int				stop_print;
	t_philo			*ph;
	sem_t			*writer_s;
	sem_t			*game_over_s;
	sem_t			*death_s;
	sem_t			*f_bowl;
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
