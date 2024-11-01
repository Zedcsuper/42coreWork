/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:13:49 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/31 20:54:33 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"
#include <stdio.h>
/*
performe a push to top elemnt of stack of one into another
stack, but returns -1 if the source stack is emty to indicate failure.
*/
static int	push(t_list **stack_to, t_list **stack_from)
{
	t_list	*tmp;
	t_list	*head_to;
	t_list	*head_from;

	if (ft_lstsize(*stack_from) == 0)
		return (-1);
	head_to = *stack_to;
	head_from = *stack_from;
	tmp = head_from;
	head_from = head_from->next;
	*stack_from = head_from;
	if (!head_to)
	{
		head_to = tmp;
		head_to->next = NULL;
		*stack_to = head_to;
	}
	else
	{
		tmp->next = head_to;
		*stack_to = tmp;
	}
	return (0);
}

/*
performs a push to top elemnt of stack b int stack a and print "pa"
to standerd input , it returns -1 if stack b is empity.
*/
int	pa(t_list **stack_a, t_list **stack_b)
{
	if (push(stack_a, stack_b) == -1)
		return (-1);
	write(1, "pa\n", 3);
	return (0);
}

/*
performe a push to top elemnt of stack a to to top stack b
and print "pb" to standernd input , returns -1 if a is empity.
*/
int	pb(t_list **stack_a, t_list **stack_b)
{
	if (push(stack_b, stack_a) == -1)
		return (-1);
	write(1, "pb\n", 3);
	return (0);
}
