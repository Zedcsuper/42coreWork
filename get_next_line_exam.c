# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if (c == 0)
		return (&s[i]);
	return (NULL);
}

char	*gnl_strdup(char *s)
{
	int		i;
	int		len;
	char	*dst;

	i = 0;
	len = gnl_strlen(s);
	dst = (char *)malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (!s1)
	{
	//	free(s1);
		return (gnl_strdup(s2));
	}
	i = 0;
	j = 0;
	tmp = (char *)malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!tmp)
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tmp[i + j] = s2[j];
		j++;
	}
	tmp[i + j] = '\0';
	free(s1);
	return (tmp);
}

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
	updated = (char *)malloc(sizeof(char) * (gnl_strlen(bufs) - i + 1));
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
	while (!gnl_strchr(bufs, '\n') && byte_read != 0)
	{
		byte_read = read(fd, tmp_buf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(tmp_buf);
			free(bufs);
			return (NULL);
		}
		tmp_buf[byte_read] = '\0';
		bufs = gnl_strjoin(bufs, tmp_buf);
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
/*
int	main(void)
{
	char	*line;
	int		fd = open("txt.txt", O_RDONLY);

	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return (0);
}
*/
