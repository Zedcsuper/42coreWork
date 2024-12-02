/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:08:10 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/24 20:37:24 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	client_pid;
static int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

static	int power_of_two (int p)
{
	int res = 1;
	while (p)
	{
		res *= 2;
		p--;
	}
	return (res);
}
	

static void	ft_atob(int pid, char c)
{
	int	bit;
	int arr[8];
	int i;

	i = 0;
	while (i < 8)
	{
		arr[i] = power_of_two(i);
		i++;
	}
	bit = 0;
	/*	
	while (bit < 8)
	{
		if ((c & (0X01 << bit)))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(400);
		bit++;
	}
	*/
	while (bit < 8)
	{
		if (c & arr[bit])
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(400);
		bit++;
	}
}

void	rec_msg(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("msg receved\n");
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;
	
	client_pid = getpid();
	ft_printf("%d\n", power_of_two(0));
	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		ft_printf("%d\n", pid);
		while (argv[2][i] != '\0')
		{
			ft_atob(pid, argv[2][i]);
			i++;
		}
		ft_atob(pid, 10);
	}
	else
	{
		ft_printf("Error\n");
		return (1);
	}
	signal(SIGUSR1, rec_msg);
	pause();
	return (0);
}
