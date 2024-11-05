/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:53:50 by zjamaien          #+#    #+#             */
/*   Updated: 2024/08/30 23:18:13 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	num_len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ar;
	int	len;
	int long	n1;

	n1 = (long)n;
	len = num_len(n1);
	ar = malloc(sizeof(char) * num_len(n1) + 1);
	if (!ar)
		return (NULL);
	if (n1 == 0)
		ar[0] = '0';
	ar[len] = '\0';
	if (n1 < 0)
	{	
		ar[0] = '-';
		n1 = -n1;
	}
	while (n1)
	{
		ar[--len] = n1 % 10 + '0';
		n1 /= 10;
	}
	return (ar);
}
/*
int	main()
{
	printf("-2147483648  %d  -10 %d 123456 %d 0 %d\n", num_len(-2147483648), num_len(-10), num_len(123456), num_len(0));
	char *nbr = ft_itoa(-2147483648);
	printf("%s\n", nbr);
	return (0);
}
*/	
