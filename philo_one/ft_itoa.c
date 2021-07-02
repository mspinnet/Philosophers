/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:44:07 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/29 16:34:52 by mspinnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	schet(int n)
{
	int		i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	put_nbr(int n)
{
	int	i;
	int	num;

	i = 1;
	if (n < 0)
		n = -n;
	num = n;
	while ((n / 10) > 0 && n != -2147483648)
	{
		n = n / 10;
		i = i * 10;
	}
	return (i);
}

static char	*minint(char *s)
{
	s = (char*)malloc(11 * sizeof(char) + 1);
	if (s == NULL)
		return (NULL);
	s = ft_memcpy(s, "-2147483648", 12);
	return (s);
}

static char	*nzero(char *s)
{
	s[0] = '0';
	s[1] = '\0';
	return (s);
}

char		*ft_itoa(int n)
{
	int		i;
	int		j;
	char	*str1;

	i = 0;
	if (n == -2147483648)
		return (minint("-2147483648"));
	str1 = (char*)malloc(sizeof(char) * (schet(n) + 1));
	if (NULL == str1)
		return (NULL);
	if (n == 0)
		return (nzero(str1));
	j = put_nbr(n);
	n < 0 ? str1[i++] = '-' : 0;
	n < 0 ? n = -n : 0;
	while (j > 0)
	{
		str1[i++] = n / j + '0';
		n = n % j;
		j = j / 10;
	}
	str1[i] = '\0';
	return (str1);
}
