/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split11.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:53:50 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/01 17:57:08 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static int	word_count(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static char	*ft_getword(const char *s1, int *index, char c)
{
	char	*copy;
	size_t	word_len;
	int		i;

	i = 0;
	word_len = 0;
	while (s1[*index + word_len] && s1[*index + word_len] != c)
		word_len++;
	copy = malloc(sizeof(char) * (word_len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[*index] && s1[*index] != c)
		copy[i++] = s1[(*index)++];
	copy[i] = '\0';
	return (copy);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		index;
	int		wc;
	int		i;

	index = 0;
	i = 0;
	if (!s)
		return (NULL);
	wc = word_count(s, c);
	arr = malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (NULL);
	while (i < wc)
	{
		while (s[index] == c && s[index])
			index++;
		arr[i] = ft_getword(s, &index, c);
		if (!arr[i])
			return (malloc_error(arr));
		i++;
	}
	arr[i] = 0;
	return (arr);
}
/*
int	main(void)
{
	char	*str;
	char	**arr;
	int		i;

	str = "hello mother fucker";
	arr = ft_split(str, ' ');
	i = 0;
	while (arr[i] != 0)
		printf("%s\n", arr[i++]);
	malloc_error(arr);
	return (0);
}
*/
