/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:55:26 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/31 18:07:27 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
