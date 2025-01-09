/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:04:02 by zjamaien          #+#    #+#             */
/*   Updated: 2025/01/10 02:26:17 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	is_overflow(const char *str)
{
	long	res;
	int		i;
	int		sign;

	res = 0;
	i = 0;
	sign = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i++] - '0');
		if ((sign == 0 && res > INT_MAX) || (sign == 1 && -res < INT_MIN))
			return (1);
	}	
	return (0);
}

static int	arg_is_number(char *av)
{
	int	i;

	i = 0;
	if (is_sign(av[i]) && av[i + 1] != '\0')
		i++;
	while (av[i] && ft_isdigit(av[i]))
		i++;
	if (av[i] != '\0' && !ft_isdigit(av[i]))
		return (0);
	return (1);
}

static int	arg_is_zero(char *av)
{
	int	i;

	i = 0;
	if (is_sign(av[i]))
		i++;
	while (av[i] && av[i] == '0')
		i++;
	if (av[i] != '\0')
		return (0);
	return (1);
}


static int	have_duplicate(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 1;
		while (av[j])
		{
			/*
			if (j != i && (nbstr_cmp(av[i], av[j]) == 0 || \
				ft_atoi(av[i]) == ft_atoi(av[j])  || ft_strlen(av[i]) > 10))
				return (1);
			*/
			if ((j != i) && (ft_atoi(av[i]) == ft_atoi(av[j])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_correct_input(char **av, int is_one_str)
{
	int	i;
	int	nb_zeros;

	nb_zeros = 0;
	if (is_one_str)
		i = 0;
	else
		i = 1;
	while (av[i])
	{
		if (!arg_is_number(av[i]) || is_overflow(av[i]) == 1)
			return (0);
		nb_zeros += arg_is_zero(av[i]);
		i++;
	}
	if (nb_zeros > 1)
		return (0);
	if (have_duplicate(av))
		return (0);
	return (1);
}
