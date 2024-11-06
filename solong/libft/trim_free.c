/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:32:32 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/06 22:39:19 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i += 1;
	}
	dest[i] = '\0';
	return (dest);
}

char	*trim_free(char *s1, char const *set)
{
	size_t	beg;
	size_t	end;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	beg = 0;
	while (s1[beg] != '\0' && ft_strchr(set, s1[beg]) != NULL)
		beg += 1;
	end = ft_strlen(s1 + beg);
	while (end > beg && ft_strchr(set, s1[end - 1]) != NULL)
		end -= 1;
	trimmed_str = malloc((end - beg + 1) * sizeof(char));
	if (!trimmed_str)
		return (NULL);
	ft_strncpy(trimmed_str, (s1 + beg), end - beg);
	trimmed_str[end - beg] = '\0';
	free(s1);
	return (trimmed_str);
} 
/*
int	main()
{
	char *s = ft_strdup("///////hi/////////////"); // Allocate memory for s1
	if (!s)
		return (1); // Handle allocation failure
	
	char *r = "/";	
	char *res = trim_free(s, r);
	printf("%s\n", res);
	free(res); // Free res after usage
	return (0);
}
*/






