/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemydov <ddemydov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:56:07 by ddemydov          #+#    #+#             */
/*   Updated: 2023/10/19 17:28:50 by ddemydov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "philo.h"

void	free_all(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->params->num_p)
		pthread_mutex_destroy(p[i].forkl);
	pthread_mutex_destroy(p->params->print);
	free(p->params->print);
	free(p->params->fork);
	free(p->params);
	free(p);
}

int	main(int argc, char **argv)
{
	t_gdata	*data;
	t_philo	*philos;

	if ((argc != 5 && argc != 6) || check_input(argv))
	{
		ft_error_input();
		exit(0);
	}
	philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	data = parse_params(argv);
	init_philos(data, philos);
	init_mutex(data, philos);
	creat_threads(philos);
	check_thread(philos);
	join_threads(philos);
	free_all(philos);
}
