/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 00:28:23 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/31 12:02:32 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
performs a reverse oeder of the linked list stack by shifting one elenmt above
returns -1 if the stacke hase less
than 2 elemnts.
*/

static int	reverse(t_list **stack)
{
	t_list	*head;
	t_list	*tail;

	if (ft_lstsize(*stack) < 2)
		return (-1);
	head = *stack;
	tail = ft_lstlast(head);
	while (head)
	{
		if (head->next->next == NULL)
		{
			head->next = NULL;
			break ;
		}
		head = head->next;
	}
	tail->next = *stack;
	*stack = tail;
	return (0);
}

/*
performs a reverse rotation to stack a
*/
int	rra(t_list **stack_a)
{
	if (reverse(stack_a) == -1)
		return (-1);
	write(1, "rra\n", 4);
	return (0);
}

/*
performe a reverse rotation to stack b
*/

int	rrb(t_list **stack_b)
{
	if (reverse(stack_b) == -1)
		return (-1);
	write(1, "rrb\n", 4);
	return (0);
}

/*
performs reverse rotaion to both stack a and b
*/
int	rrr(t_list **stack_a, t_list **stack_b)
{
	if (reverse(stack_a) == -1 || reverse(stack_b) == -1)
		return (-1);
	write(1, "rrr\n", 4);
	return (0);
}
