/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:10:39 by mspinnet          #+#    #+#             */
/*   Updated: 2021/04/09 12:22:38 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	if_died(t_all *all)
{
	all->args->flag_died = 1;
	usleep(10);
	printf("%lld %s died\n", current_time() - all->args->time,
		all->philo->name);
	sem_post(all->sem->sem_eat);
}

void	*died_check(void *args)
{
	t_all	*all;
	int		i;
	int		j;

	j = 0;
	all = (t_all *)args;
	while (1)
	{
		i = -1;
		while (++i < all->args->num_philo)
		{
			if ((current_time() - all[i].philo->eat > all->args->time_to_die)
				&& all[i].philo->flag == 0)
			{
				if_died(&all[i]);
				return (NULL);
			}
			j = num_eat(&all[i], j);
			if (j == all->args->num_philo)
			{
				all->args->flag_died = 1;
				return (NULL);
			}
		}
	}
}

void	eat_sem(t_all *all)
{
	long long int	time;
	long long int	time2;

	sem_wait(all->sem->sem_eat);
	print_it(all, all->philo->name, " has taken a fork\n");
	sem_wait(all->sem->sem_eat);
	print_it(all, all->philo->name, " has taken a fork\n");
	all->philo->eat = current_time();
	print_it(all, all->philo->name, " is eating\n");
	all->philo->flag = 1;
	time2 = current_time() - all->args->time;
	time = current_time() - all->args->time;
	while (time < time2 + all->args->time_to_eat && all->args->flag_died != 1)
	{
		time = current_time() - all->args->time;
		usleep(100);
	}
	sem_post(all->sem->sem_eat);
	sem_post(all->sem->sem_eat);
	all->philo->flag = 0;
	if (all->args->num_eat != 0)
		all->philo->num_eating--;
}

void	*eat(void *args)
{
	t_all			*all;
	long long int	time;
	long long int	time2;

	all = (t_all *)args;
	while (all->args->flag_died == 0)
	{
		usleep(10);
		eat_sem(all);
		print_it(all, all->philo->name, " is sleeping\n");
		time2 = current_time() - all->args->time;
		while (time < time2 + all->args->time_to_sleep
			&& all->args->flag_died != 1)
		{
			time = current_time() - all->args->time;
			usleep(100);
		}
		usleep(10);
		print_it(all, all->philo->name, " is thinking\n");
	}
	return (NULL);
}

void	print_it(t_all *all, char *name, char *message)
{
	long long int		time;

	sem_wait(all->sem->sem_print);
	if (all->args->flag_died == 1)
	{
		sem_post(all->sem->sem_print);
		return ;
	}
	time = current_time();
	time = time - all->args->time;
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	write(1, name, ft_strlen(name));
	write(1, message, ft_strlen(message));
	sem_post(all->sem->sem_print);
}
