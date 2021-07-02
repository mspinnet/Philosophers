/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:51:28 by mspinnet          #+#    #+#             */
/*   Updated: 2021/04/09 19:40:29 by mspinnet         ###   ########.fr       */
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
		if (i == (args->num_philo - 1))
		{
			init_philo(&philo[i], ft_itoa(i), i, 0);
			philo[i].eat = args->time;
			philo[i].num_eating = args->num_eat;
			if (args->num_eat == 0)
				philo[i].num_eating = -1;
			break ;
		}
		init_philo(&philo[i], ft_itoa(i), i, i + 1);
		philo[i].eat = args->time;
		philo[i].num_eating = args->num_eat;
		if (args->num_eat == 0)
			philo[i].num_eating = -1;
		i++;
	}
	return (philo);
}

void	init_all2(t_all *all, t_philo *philo, t_table *table, t_args *args)
{
	int i;

	i = 0;
	while (i < args->num_philo)
	{
		all[i].philo = &philo[i];
		all[i].table = table;
		all[i].args = args;
		i++;
	}
}

t_all	*init_all(t_args *args, pthread_t *threads)
{
	t_all		*all;
	t_philo		*philo;
	t_table		table;
	int			i;

	all = malloc(sizeof(t_all) * args->num_philo);
	philo = init_philo2(args);
	init_table(&table, args->num_philo);
	init_all2(all, philo, &table, args);
	i = 0;
	pthread_create(&threads[all->args->num_philo], NULL, died_check, all);
	while (i < args->num_philo)
	{
		pthread_create(&threads[i], NULL, eat, &all[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i <= args->num_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (all);
}

int		check_valid(int argc, char **argv)
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

int		main(int argc, char **argv)
{
	pthread_t	*threads;
	t_all		*all;
	t_args		args;

	args.time = current_time();
	args.flag_died = 0;
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
	threads = malloc(sizeof(pthread_t) * (args.num_philo + 1));
	pthread_mutex_init(&args.stop, NULL);
	all = init_all(&args, threads);
	return (0);
}
