/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:59:32 by zjamaien          #+#    #+#             */
/*   Updated: 2024/09/18 13:53:08 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_bufs(char *bufs)
{
	size_t	i;
	size_t	j;
	char	*updated;

	i = 0;
	while (bufs[i] && bufs[i] != '\n')
		i++;
	if (!bufs[i])
	{
		free(bufs);
		return (NULL);
	}
	if (bufs[i] == '\n')
		i++;
	updated = (char *)malloc(sizeof(char) * (ft_strlen(bufs) - i + 1));
	if (!updated)
		return (NULL);
	j = -1;
	while (bufs[i + (++j)])
		updated[j] = bufs[i + j];
	updated[j] = '\0';
	free(bufs);
	return (updated);
}

char	*get_line_from_buf(char *bufs)
{
	size_t	i;
	char	*line;

	if (!bufs[0])
		return (NULL);
	i = 0;
	while (bufs[i] && bufs[i] != '\n')
		i++;
	if (bufs[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (bufs[i] && bufs[i] != '\n')
	{
		line[i] = bufs[i];
		i++;
	}
	if (bufs[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*add_bufs(int fd, char *bufs)
{
	char	*tmp_buf;
	int		byte_read;

	tmp_buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp_buf)
		return (NULL);
	byte_read = 1;
	while (!ft_strchr(bufs, '\n') && byte_read != 0)
	{
		byte_read = read(fd, tmp_buf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(tmp_buf);
			free(bufs);
			return (NULL);
		}
		tmp_buf[byte_read] = '\0';
		bufs = ft_strjoin(bufs, tmp_buf);
	}
	free(tmp_buf);
	return (bufs);
}

char	*get_next_line(int fd)
{
	static char	*bufs;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bufs = add_bufs(fd, bufs);
	if (!bufs)
		return (NULL);
	line = get_line_from_buf(bufs);
	bufs = update_bufs(bufs);
	return (line);
}
