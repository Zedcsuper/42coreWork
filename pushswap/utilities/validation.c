/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:47:22 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/30 23:11:05 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
check if given input integer is present in a given array of string.
return 1 if the integer is present and 0 elswise
*/

static int	ft_contains(int num, char **argv, int i)
{
	i++;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == num)
			return (1);
		i++;
	}
	return (0);
}

/*
check if a given string represnt a valid integer number.
*/

static int	ft_isnum(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '-' || num[0] == '+')
		i++;
	if ((num[0] == '-' || num[0] == '+') && !num[1])
		return (0);
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
takes a string argument av and splits it into array of string
*/
static char	**argc2(char *av)
{
	char	**args;

	args = ft_split(av, ' ');
	return (args);
}

/*
check the validity of the arguments passed to the program
which must be integers without duplicate and within the
range of an int . it also handels the case when the arguments
are passed as a single string seprated by space".
*/
void	check_args(int argc, char **argv)
{
	int		i;
	long	tmp;
	char	**args;

	i = 1;
	if (argc == 2)
		args = argc2(argv[1]);
	else
		args = argv;
	while (args[i])
	{
		tmp = ft_atoi(args[i]);
		if (!ft_isnum(args[i]))
			error_message();
		if (ft_contains(tmp, args, i) == 1)
			error_message();
		if (tmp < INT_MIN || tmp > INT_MAX)
			error_message();
		i++;
	}
	if (argc == 2)
		free_string(args);
}
