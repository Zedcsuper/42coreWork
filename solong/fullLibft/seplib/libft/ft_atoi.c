/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:53:50 by zjamaien          #+#    #+#             */
/*   Updated: 2024/08/23 22:04:31 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		res = (res * 10) + (str[i++] - '0');
	return (res * sign);
}
/*
int main()
{
    printf("ft_atoi results:\n");
    printf("Input: \"-1\"         => %d\n", ft_atoi("-1"));
    printf("Input: \"      +9\"   => %d\n", ft_atoi("      +9"));
    printf("Input: \"123abc\"     => %d\n", ft_atoi("123abc"));
    printf("Input: \"-+33\"       => %d\n", ft_atoi("-+33"));
    printf("Input: \"   42\"      => %d\n", ft_atoi("   42"));
    printf("Input: \"abc123\"     => %d\n", ft_atoi("abc123"));

    printf("\nStandard atoi results:\n");
    printf("Input: \"-1\"         => %d\n", atoi("-1"));
    printf("Input: \"      +9\"   => %d\n", atoi("      +9"));
    printf("Input: \"123abc\"     => %d\n", atoi("123abc"));
    printf("Input: \"-+33\"       => %d\n", atoi("-+33"));
    printf("Input: \"   42\"      => %d\n", atoi("   42"));
    printf("Input: \"abc123\"     => %d\n", atoi("abc123"));

    return 0;
}
*/
