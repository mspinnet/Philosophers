/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:03:14 by mspinnet          #+#    #+#             */
/*   Updated: 2021/04/10 15:54:31 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*eat_check(void *args)
{
	t_all	*all;
	int		i;

	all = (t_all *)args;
	i = 0;
	while (1)
	{
		sem_wait(all->sem->sem_num);
		i++;
		if (i == all->args->num_philo)
		{
			sem_post(all->sem->sem_kill);
			return (NULL);
		}
	}
}

size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putnbr_fd(long int n, int fd)
{
	int			i;
	long int	res;
	long int	num;

	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
	}
	i = 1;
	num = n;
	while ((n / 10) > 0 && n != -2147483648)
	{
		n = n / 10;
		i = i * 10;
	}
	while (i > 0 && n != -2147483648)
	{
		res = (num / i) + '0';
		num = num % i;
		write(fd, &res, 1);
		i = i / 10;
	}
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	const char		*str2;

	str1 = dst;
	str2 = src;
	i = 0;
	if (dst == '\0' && src == '\0')
		return (NULL);
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (dst);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
