/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:53:50 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/01 17:57:08 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (NULL);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len--)
			*((unsigned char *)(dst + len)) = *((unsigned char *)(src + len));
	}
	return (dst);
}
/*
int	main(void)
{
	char	str1[] = "12345";
	char	str[] = "12345";

	printf("str = %p \n str + 2 = %p\n", &str1, &*(str1 + 2));
	ft_memcpy(str1 + 2, str1, 3);
	printf("cpy  %s\n", str1);
	printf("org  %s\n", str);
	ft_memmove(str + 2, str, 3);
	printf("mov  %s\n", str);
	return (0);
}
*/
