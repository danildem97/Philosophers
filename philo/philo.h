/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemydov <ddemydov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:03:02 by ddemydov          #+#    #+#             */
/*   Updated: 2023/10/18 16:52:59 by ddemydov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_gdata
{
	int				tte;
	int				ttd;
	int				tts;
	int				tme;
	int				over;
	int				num_p;
	int				check_tme;
	int				eated;
	pthread_mutex_t	*print;
	pthread_mutex_t	*fork;
}				t_gdata;

typedef struct s_philo
{
	int				id;
	int				iter;
	long int		start;
	long int		meal;
	pthread_t		thread;
	pthread_mutex_t	*forkl;
	pthread_mutex_t	*forkr;
	t_gdata			*params;
}				t_philo;

void		ft_print(t_philo *p, int i);
int			ft_atoi(const char *nptr);
void		ft_error_input(void);
uint64_t	time_now(void);
int			check_input(char **argv);
t_gdata		*parse_params(char **argv);
void		init_mutex(t_gdata *data, t_philo *philo);
void		init_philos(t_gdata *data, t_philo *philo);
void		creat_threads(t_philo *philo);
void		*routine(void *p);
void		ft_usleep(long int time);
void		join_threads(t_philo *p);
int			check_death(t_philo *philo);
void		check_thread(t_philo *philo);

#endif