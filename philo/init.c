/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemydov <ddemydov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:31 by ddemydov          #+#    #+#             */
/*   Updated: 2023/10/19 17:28:58 by ddemydov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	long int	time;

	pthread_mutex_lock(philo->params->print);
	time = time_now() - philo->meal;
	if (time >= philo->params->ttd)
	{
		pthread_mutex_unlock(philo->params->print);
		ft_print(philo, 5);
		pthread_mutex_unlock(philo->forkl);
		pthread_mutex_unlock(philo->forkr);
		return (1);
	}
	pthread_mutex_unlock(philo->params->print);
	return (0);
}

void	init_philos(t_gdata *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_p)
	{
		philo[i].id = i + 1;
		philo[i].start = 0;
		philo[i].meal = 0;
		philo[i].thread = 0;
		philo[i].forkl = &data->fork[i];
		if (philo[i].id == data->num_p)
			philo[i].forkr = &data->fork[0];
		else
			philo[i].forkr = &data->fork[i + 1];
		philo[i].params = data;
		philo[i].iter = 0;
		i++;
	}
}

void	init_mutex(t_gdata *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_p)
	{
		pthread_mutex_init(philo[i].forkl, NULL);
		i++;
	}
	pthread_mutex_init(data->print, NULL);
}

void	creat_threads(t_philo *philo)
{
	int				i;
	long int		j;

	i = 0;
	j = time_now();
	while (i < philo->params->num_p)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		philo[i].start = j;
		philo[i].meal = j;
		i++;
	}
}

void	join_threads(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->params->num_p)
		pthread_join(p[i].thread, (void *)&p[i]);
}
