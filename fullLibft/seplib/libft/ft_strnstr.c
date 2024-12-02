/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:53:50 by zjamaien          #+#    #+#             */
/*   Updated: 2024/08/27 16:01:56 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *bg, const char *lt, size_t len)
{
	size_t	i;
	size_t	nlen;

	if (*lt == 0)
		return ((char *) bg);
	i = 0;
	nlen = ft_strlen(lt);
	while (i < len && bg[i])
	{
		if (bg[i] == *lt && (len - i >= nlen) && !ft_strncmp(&bg[i], lt, nlen))
			return ((char *)&bg[i]);
		i++;
	}
	return (NULL);
}
