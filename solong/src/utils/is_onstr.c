/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_onstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:33:54 by zjamaien          #+#    #+#             */
/*   Updated: 2024/12/03 20:55:02 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

bool	is_onstr(const char *str, int ch)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] == ch)
			return (true);
		i++;
	}
	return (false);
}
