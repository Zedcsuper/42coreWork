/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:15:35 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/30 21:18:57 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
add a new node to the end of list
*/

void	ft_lstadd_back(t_list **stack, t_list *new)
{
	t_list	*node;

	if (*stack)
	{
		node = ft_lstlast(*stack);
		node->next = new;
		new->next = NULL;
	}
	else
	{
		*stack = new;
		(*stack)->next = NULL;
	}
}
