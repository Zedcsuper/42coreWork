/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:50:04 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/30 21:03:52 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
creates a new node for linked list with the given integer value.
Allocates memory for the new node using malloc and sets the initial
values for the node's value, index, and next pointer.
-1 to represnt an unset or invalid index value.
return a pointer to the newly created node.
*/
t_list	*ft_lstnew(int value)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = value;
	new->index = -1;
	new->next = NULL;
	return (new);
}
