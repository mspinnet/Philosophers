/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:09:42 by mspinnet          #+#    #+#             */
/*   Updated: 2021/04/09 19:41:26 by mspinnet         ###   ########.fr       */
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

void			init_philo(t_philo *philo, char *name)
{
	philo->name = name;
	philo->eat = 0;
}

t_semaphor		init_sem(t_args *args)
{
	t_semaphor	sem;

	sem_unlink("sema");
	sem.sem_eat = sem_open("sema", O_CREAT, 0666, args->num_philo);
	sem_unlink("sema2");
	sem.sem_print = sem_open("sema2", O_CREAT, 0666, 1);
	sem_unlink("sema3");
	sem.sem_died = sem_open("sema3", O_CREAT, 0666, 1);
	sem_unlink("sema4");
	sem.sem_kill = sem_open("sema4", O_CREAT, 0666, 0);
	sem_unlink("sema5");
	sem.sem_num = sem_open("sema5", O_CREAT, 0666, 0);
	return (sem);
}

int				check_valid(int argc, char **argv)
{
	int		i;
	int		j;
	int		res;

	i = 0;
	res = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
		}
		res = ft_atoi(argv[1]);
		if (res > 200)
			return (1);
		res = ft_atoi(argv[i]);
		if (res == 0)
			return (1);
	}
	return (0);
}
