/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:57:08 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/01 17:57:08 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int	main(int ac, char *argv[], char *envp[])
{

	pid_t	pidid;
	int	fd[2];

	if (pipe(fd) == -1)
		perror("");
	pidid = fork();
	if (pidid == -1)
		perror("");
	if (pidid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		printf("write end\n");
		sleep(1);
		if (execve("/bin/ls", (char *[]){"ls", "-l", NULL}, envp))
			perror("");
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	printf("read end\n");
	if (execve("/usr/bin/grep", (char *[]){"grep", "p", NULL}, envp))
		perror("");
	waitpid(pidid, NULL, 0);
	sleep(100);


/*	
	
	int i = 0;
	while (envp[i])
	{
		printf("envp[%d] = %s\n", i, envp[i]);
		i++;
	}
*/	
	/*
	int fd = open("txt.txt", O_RDONLY);
	if (fd == -1)
		perror("");
	*/
	return (0);
}
