/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:42:55 by zjamaien          #+#    #+#             */
/*   Updated: 2024/12/02 19:19:31 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_gnlstrlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_gnlstrchr(char *s, int c)
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

char	*ft_gnlstrdup(char *s)
{
	int		i;
	int		len;
	char	*dst;

	i = 0;
	len = ft_gnlstrlen(s);
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

char	*ft_gnlstrjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (!s1)
		return (ft_gnlstrdup(s2));
	i = 0;
	j = 0;
	tmp = (char *)malloc(ft_gnlstrlen(s1) + ft_gnlstrlen(s2) + 1);
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
