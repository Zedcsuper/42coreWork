/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:00:50 by zjamaien          #+#    #+#             */
/*   Updated: 2024/09/18 22:24:09 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_len(int n, int *len)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*len) += 11;
		return ;
	}
	if (n < 0)
	{
		ft_putchar_len('-', len);
		ft_putnbr_len(n * -1, len);
	}
	else
	{
		if (n > 9)
			ft_putnbr_len(n / 10, len);
		ft_putchar_len(n % 10 + '0', len);
	}
}

void	ft_putptr_len(size_t pointer, int *len)
{
	char	string[25];
	int		i;
	char	*base_char;

	if (!pointer)
	{
		ft_putstr_len("(nil)", len);
		return ;
	}
	base_char = "0123456789abcdef";
	i = 0;
	write(1, "0x", 2);
	(*len) += 2;
	if (pointer == 0)
	{
		ft_putchar_len('0', len);
		return ;
	}
	while (pointer != 0)
	{
		string[i++] = base_char[pointer % 16];
		pointer = pointer / 16;
	}
	while (i--)
		ft_putchar_len(string[i], len);
}

void	ft_hex_len(unsigned int x, int *len, char xX)
{
	char	string[25];
	char	*base_char;
	int		i;

	if (xX == 'x')
		base_char = "0123456789abcdef";
	else
		base_char = "0123456789ABCDEF";
	i = 0;
	if (x == 0)
	{
		ft_putchar_len('0', len);
		return ;
	}
	while (x != 0)
	{
		string[i] = base_char[x % 16];
		x = x / 16;
		i++;
	}
	while (i--)
		ft_putchar_len(string[i], len);
}

void	ft_putunsignednbr_len(unsigned int u, int *len)
{
	if (u > 9)
		ft_putunsignednbr_len(u / 10, len);
	ft_putchar_len(u % 10 + '0', len);
}
