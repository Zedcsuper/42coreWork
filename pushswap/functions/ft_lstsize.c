/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:59:26 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/01 17:07:16 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
takes a pointer to the begining of a linked list
and returns the number of elemnts (nodes) in the list.
*/

int	ft_lstsize(t_list *head)
{
	size_t	i;
	t_list	*tmp;

	tmp = head;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
