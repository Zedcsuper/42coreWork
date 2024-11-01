/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:04:39 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/30 21:10:08 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
iterate over the list ,starting from the head and following the next pointers
unitl it reaches the last node, which is the one with next = null.
once it reaches that node, it returns a pointer to it.
*/

t_list	*ft_lstlast(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
			return (tmp);
	}
	return (tmp);
}
