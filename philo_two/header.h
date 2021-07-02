/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:55:58 by mspinnet          #+#    #+#             */
/*   Updated: 2021/04/09 12:19:44 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct	s_philo
{
	char			*name;
	long long int	eat;
	int				num_eating;
	int				flag;
}				t_philo;

typedef struct	s_args
{
	int					num_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_eat;
	long long int		time;
	int					flag_died;
	pthread_mutex_t		stop;
}				t_args;

typedef struct	s_semaphor
{
	sem_t		*sem_eat;
	sem_t		*sem_print;
}				t_semaphor;

typedef struct	s_all
{
	t_philo		*philo;
	t_args		*args;
	t_semaphor	*sem;
}				t_all;

int				main(int argc, char **argv);
char			*ft_itoa(int n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_putnbr_fd(long int n, int fd);
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
long long int	current_time(void);
void			init_philo(t_philo *philo, char *name);
void			print_it(t_all *all, char *name, char *message);
void			if_died(t_all *all);
void			*died_check(void *args);
void			eat_sem(t_all *all);
void			*eat(void *args);
t_philo			*init_philo2(t_args *args);
void			init_all2(t_all *all, t_philo *philo, t_args *args,
					t_semaphor *sem);
t_all			*init_all(t_args *args, pthread_t *threads, t_semaphor *sem);
t_semaphor		init_sem(t_args *args);
int				check_valid(int argc, char **argv);
int				ft_isdigit(int c);
int				num_eat(t_all *all, int j);

#endif
