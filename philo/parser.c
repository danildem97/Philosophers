/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemydov <ddemydov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:04:51 by ddemydov          #+#    #+#             */
/*   Updated: 2023/10/19 17:05:34 by ddemydov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_thread(t_philo *philo)
{
	int	i;

	while (!philo->params->over)
	{
		i = 0;
		while (i < philo->params->num_p)
		{
			if (check_death(&philo[i]))
				philo->params->over = 1;
			i++;
		}
		if (philo->params->eated == philo->params->num_p)
			philo->params->over = 1;
	}
	return ;
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_number(char *arg)
{
	int	index;

	index = 0;
	while (arg[index])
	{
		if (!is_digit(arg[index]))
			return (0);
		index++;
	}
	return (1);
}

int	check_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_number(argv[i]))
			return (1);
		i++;
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0
		|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0
		|| (argv[5] && ft_atoi(argv[5]) <= 0))
		return (1);
	return (0);
}

t_gdata	*parse_params(char **argv)
{
	t_gdata	*new_data;

	new_data = malloc(sizeof(t_gdata));
	if (!new_data)
		return (NULL);
	new_data->print = malloc(sizeof(pthread_mutex_t));
	if (!new_data->print)
		return (NULL);
	new_data->fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!new_data->fork)
		return (NULL);
	new_data->num_p = ft_atoi(argv[1]);
	new_data->ttd = ft_atoi(argv[2]);
	new_data->tte = ft_atoi(argv[3]);
	new_data->tts = ft_atoi(argv[4]);
	new_data->check_tme = 0;
	if (argv[5])
	{
		new_data->check_tme = 1;
		new_data->tme = ft_atoi(argv[5]);
	}
	new_data->over = 0;
	new_data->eated = 0;
	return (new_data);
}
