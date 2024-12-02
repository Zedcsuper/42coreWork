/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:54:44 by zjamaien          #+#    #+#             */
/*   Updated: 2024/12/02 19:20:13 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_len(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_putstr_len(char *s, int *len)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		(*len) += 6;
		return ;
	}
	while (s[i])
	{
		ft_putchar_len(s[i], len);
		i++;
	}
}
