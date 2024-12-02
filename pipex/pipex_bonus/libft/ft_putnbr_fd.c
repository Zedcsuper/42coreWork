/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:53:50 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/01 17:57:07 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb < 10)
		ft_putchar_fd(nb + '0', fd);
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
}
/*
int	main(void)
{
	int				fd;
	unsigned int	x;

	fd = open("txt1.txt", O_RDWR | O_CREAT, 0644);
	ft_putnbr_fd(-2147483648, fd);
	x = -99;
	printf("%u\n", x);
	return (0);
}
*/
