/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:53:50 by zjamaien          #+#    #+#             */
/*   Updated: 2024/08/27 15:53:23 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd(*(s++), fd);
}
/*
int	main()
{
	int fd = open("txt.txt", O_RDWR | O_CREAT);
	ft_putstr_fd("hi every body", fd);
	close(fd);
	return (0);
}
*/
