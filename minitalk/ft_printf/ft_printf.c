/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:25:13 by zjamaien          #+#    #+#             */
/*   Updated: 2024/09/18 21:48:08 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_type(char c, va_list *args, int *len, int *i)
{
	if (c == 's')
		ft_putstr_len(va_arg(*args, char *), len);
	else if (c == 'd' || c == 'i')
		ft_putnbr_len(va_arg(*args, int), len);
	else if (c == 'u')
		ft_putunsignednbr_len(va_arg(*args, unsigned int), len);
	else if (c == 'x')
		ft_hex_len(va_arg(*args, unsigned int), len, 'x');
	else if (c == 'X')
		ft_hex_len(va_arg(*args, unsigned int), len, 'X');
	else if (c == 'p')
		ft_putptr_len(va_arg(*args, size_t), len);
	else if (c == 'c')
		ft_putchar_len(va_arg(*args, int), len);
	else if (c == '%')
		ft_putchar_len('%', len);
	else
		(*i)--;
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			ft_printf_type(format[i], &args, &len, &i);
			i++;
		}
		else
		{
			ft_putchar_len((char)format[i], &len);
			i++;
		}
	}
	va_end(args);
	return (len);
}
