/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:51:28 by mspinnet          #+#    #+#             */
/*   Updated: 2021/04/10 15:54:39 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_philo	*init_philo2(t_args *args)
{
	t_philo		*philo;
	int			i;

	philo = malloc(sizeof(t_philo) * args->num_philo);
	i = 0;
	while (i < args->num_philo)
	{
		init_philo(&philo[i], ft_itoa(i));
		philo[i].eat = args->time;
		philo[i].num_eating = args->num_eat;
		if (args->num_eat == 0)
			philo[i].num_eating = -1;
		i++;
	}
	return (philo);
}

void	init_all2(t_all *all, t_philo *philo, t_args *args, t_semaphor *sem)
{
	int i;

	i = 0;
	while (i < args->num_philo)
	{
		all[i].philo = &philo[i];
		all[i].args = args;
		all[i].sem = sem;
		i++;
	}
}

void	kill_all(t_all *all, t_args *args)
{
	int			i;

	i = 0;
	while (i < args->num_philo)
	{
		sem_wait(all->sem->sem_kill);
		while (i < args->num_philo)
			kill(all[i++].pid, SIGINT);
	}
	sem_close(all->sem->sem_eat);
	sem_close(all->sem->sem_print);
	sem_close(all->sem->sem_died);
	sem_close(all->sem->sem_kill);
	sem_close(all->sem->sem_num);
}

t_all	*init_all(t_args *args, pthread_t *threads, t_semaphor *sem)
{
	t_all		*all;
	t_philo		*philo;
	int			i;

	all = malloc(sizeof(t_all) * args->num_philo);
	philo = init_philo2(args);
	init_all2(all, philo, args, sem);
	if (args->num_eat != 0 && args->num_philo > 1)
		pthread_create(&threads[args->num_philo], NULL, eat_check, all);
	i = 0;
	while (i < args->num_philo)
	{
		all[i].pid = fork();
		if (all[i].pid == -1)
			exit(0);
		if (all[i].pid == 0)
		{
			pthread_create(&threads[i], NULL, died_check, &all[i]);
			eat(&all[i]);
			break ;
		}
		i++;
	}
	kill_all(all, args);
	return (all);
}

int		main(int argc, char **argv)
{
	pthread_t	*threads;
	t_all		*all;
	t_semaphor	sem;
	t_args		args;

	args.time = current_time();
	if (argc == 6 && check_valid(argc, argv) == 0)
		args.num_eat = ft_atoi(argv[5]);
	else if (argc == 5 && check_valid(argc, argv) == 0)
		args.num_eat = 0;
	else if (argc < 5 || argc > 6 || check_valid(argc, argv) == 1)
		return (write(1, "Erorr arguments\n", 16));
	args.num_philo = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	args.flag = 0;
	sem = init_sem(&args);
	threads = malloc(sizeof(pthread_t) * (args.num_philo + 1));
	all = init_all(&args, threads, &sem);
	return (0);
}
