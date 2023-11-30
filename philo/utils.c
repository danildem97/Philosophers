/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemydov <ddemydov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:22:41 by ddemydov          #+#    #+#             */
/*   Updated: 2023/09/20 17:26:31 by ddemydov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	time_now(void)
{
	uint64_t		milliseconds;
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_usleep(long int time)
{
	long int	start_time;

	start_time = time_now();
	while ((time_now() - start_time) < (unsigned long long) time)
		usleep(150);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	sum;

	sum = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		sum *= 10;
		sum += nptr[i] - '0';
		i++;
	}
	sum *= sign;
	return (sum);
}

void	ft_print(t_philo *p, int i)
{
	pthread_mutex_lock(p->params->print);
	if (p->params->over)
	{
		pthread_mutex_unlock(p->params->print);
		return ;
	}
	if (i == 1)
		printf("%llu %d is eating\n", time_now() - p->start, p->id);
	else if (i == 2)
		printf("%llu %d is sleeping\n", time_now() - p->start, p->id);
	else if (i == 3)
		printf("%llu %d is thinking\n", time_now() - p->start, p->id);
	else if (i == 4)
		printf("%llu %d has taken fork\n", time_now() - p->start, p->id);
	else if (i == 5)
		printf("%llu %d died\n", time_now() - p->start, p->id);
	pthread_mutex_unlock(p->params->print);
}

void	ft_error_input(void)
{
	printf("Wrong input!\n");
	printf("Following args are needed or allowed\n");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
}
