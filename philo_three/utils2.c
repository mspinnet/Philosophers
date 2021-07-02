/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:10:39 by mspinnet          #+#    #+#             */
/*   Updated: 2021/04/10 15:54:36 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	if_died(t_all *all)
{
	int		i;

	i = -1;
	sem_wait(all->sem->sem_died);
	sem_wait(all->sem->sem_print);
	usleep(10);
	printf("%lld %s died\n", current_time() - all->args->time,
		all->philo->name);
	if (all->args->num_eat != 0)
		while (++i < all->args->num_philo)
			sem_post(all->sem->sem_num);
	else if (all->args->num_eat == 0)
		sem_post(all->sem->sem_kill);
}

void	*died_check(void *args)
{
	t_all	*all;
	int		i;

	all = (t_all *)args;
	i = -1;
	while (1)
	{
		if ((current_time() - all->philo->eat > all->args->time_to_die)
			&& all->args->flag == 0)
		{
			if_died(all);
			return (NULL);
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
	all->args->flag = 1;
	time2 = current_time() - all->args->time;
	time = current_time() - all->args->time;
	while (time < time2 + all->args->time_to_eat)
	{
		time = current_time() - all->args->time;
		usleep(100);
	}
	sem_post(all->sem->sem_eat);
	sem_post(all->sem->sem_eat);
	all->args->flag = 0;
	if (all->args->num_eat != 0)
		all->philo->num_eating--;
	if (all->philo->num_eating == 0)
		sem_post(all->sem->sem_num);
}

void	*eat(t_all *all)
{
	long long int	time;
	long long int	time2;

	time = 0;
	while (1)
	{
		usleep(100);
		eat_sem(all);
		print_it(all, all->philo->name, " is sleeping\n");
		time2 = current_time() - all->args->time;
		while (time < time2 + all->args->time_to_sleep)
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
	time = current_time();
	time = time - all->args->time;
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	write(1, name, ft_strlen(name));
	write(1, message, ft_strlen(message));
	sem_post(all->sem->sem_print);
}
