/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemydov <ddemydov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:44:50 by ddemydov          #+#    #+#             */
/*   Updated: 2023/10/23 18:07:23 by ddemydov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->forkl);
	ft_print(philo, 4);
	pthread_mutex_lock(philo->forkr);
	ft_print(philo, 4);
	philo->meal = time_now();
	philo->iter++;
	ft_print(philo, 1);
	ft_usleep(philo->params->tte);
	pthread_mutex_unlock(philo->forkl);
	pthread_mutex_unlock(philo->forkr);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id & 1)
		ft_usleep(philo->params->tte * 0.9 + 1);
	while (!philo->params->over)
	{
		p_eat(philo);
		pthread_mutex_lock(philo->params->print);
		if (philo->params->check_tme && philo->iter == philo->params->tme)
		{
			philo->params->eated++;
			pthread_mutex_unlock(philo->params->print);
			return (0);
		}
		pthread_mutex_unlock(philo->params->print);
		ft_print(philo, 2);
		ft_usleep(philo->params->tts);
		ft_print(philo, 3);
	}
	return (0);
}
