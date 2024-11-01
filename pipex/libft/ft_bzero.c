/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:53:50 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/01 17:57:08 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
/*
void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*((unsigned char *)(s + n)) = 0;
}
*/
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr++ = 0;
	}
}
/*
void	print_bin(int n)
{
	char c;
	int i = 1;
	long l = 1;
	l <<= 32;
	while (l >>= 1)
	{
		c = (n & l);
		if (c)
			printf("1");
		else
			printf("0");
		if (i % 8 == 0 && i != 32)
			printf(".");
		i++;
	}
	printf("\n");
}

void	set_bit(int *n, int pos, int value)
{
	if (value)
		*n |= (1 << pos);
	else
		*n &= ~(1 << pos);
}

int	main()
{
	int arr[] = {19999999, 2 , 3};
	print_bin(4);
	set_bit(&arr[2], 1, 0);
	int i = 0;
	while (i < 3)
		printf("%d ", arr[i++]);
	printf("\n");
	i = 0;
	ft_bzero(arr, 1);

	while (i < 3)
		printf("%d ", arr[i++]);
	printf("\n");
	ft_bzero(arr, 2);
	i = 0;
	while (i < 3)
		printf("%d ", arr[i++]);
	printf("\n");
	return (0);
}
*/
