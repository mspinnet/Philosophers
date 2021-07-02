/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:09:42 by mspinnet          #+#    #+#             */
/*   Updated: 2021/04/09 12:16:17 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				ft_atoi(const char *str)
{
	int						i;
	unsigned long long int	res;
	int						znak;

	i = 0;
	znak = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			znak = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	znak == 1 && res > 9223372036854775807 ? res = -1 : 0;
	znak == -1 && res > 9223372036854775807 ? res = 0 : 0;
	return (res * znak);
}

long long int	current_time(void)
{
	struct timeval		milisec;
	long long int		time;

	gettimeofday(&milisec, NULL);
	time = milisec.tv_sec * 1000 + (milisec.tv_usec / 1000);
	return (time);
}

void			init_philo(t_philo *philo, char *name, int left, int right)
{
	philo->name = name;
	philo->left = left;
	philo->rigth = right;
	philo->eat = 0;
	philo->flag = 0;
}

void			init_table(t_table *table, int num_philo)
{
	int i;

	i = 0;
	table->fork = malloc(sizeof(pthread_mutex_t) * num_philo);
	while (i < num_philo)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		i++;
	}
}

void			print_it(t_all *all, char *name, char *message)
{
	long long int		time;

	pthread_mutex_lock(&all->args->stop);
	if (all->args->flag_died == 1)
	{
		pthread_mutex_unlock(&all->args->stop);
		return ;
	}
	time = current_time();
	time = time - all->args->time;
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	write(1, name, ft_strlen(name));
	write(1, message, ft_strlen(message));
	pthread_mutex_unlock(&all->args->stop);
}
