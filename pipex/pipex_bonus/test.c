/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:57:08 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/01 17:57:08 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main()
{
	int	fd[2];
	pid_t	pidid;
	char	str[50];
	char	readstr[4];
	if (pipe(fd) == -1)
		perror("");
	pidid = fork();
	if (pidid == 0)
	{
		close(fd[0]);
		str[0] = 'h'; str[1] = 'e'; str[2] = 'l'; str[3] = '\0';
		write(fd[1], str, 4);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		read(fd[0], readstr, 4);
		printf("%s", readstr);
		close(fd[0]);
		waitpid(pidid, NULL, 0);
	}
	return (0);
}
