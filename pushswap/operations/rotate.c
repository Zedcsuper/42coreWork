/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:17:18 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/31 20:56:39 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
perform rotation on the linked list moibig first elenmt to thend
and return -1 if stack has less then 2 elemnt
*/
static int	rotate(t_list **stack)
{
	t_list	*head;
	t_list	*tail;

	if (ft_lstsize(*stack) < 2)
		return (-1);
	head = *stack;
	tail = ft_lstlast(head);
	*stack = head->next;
	head->next = NULL;
	tail->next = head;
	return (0);
}

/*
performs a rotation of a linked list stack (a) by moving its
first elemnt to the end. print "ra".
*/
int	ra(t_list **stack_a)
{
	if (rotate(stack_a) == -1)
		return (-1);
	write(1, "ra\n", 3);
	return (0);
}

/*
performs rataion on stack (b) by shift first elemnt to end seconde elemnt become
first last elemnt becoe before last.
*/
int	rb(t_list **stack_b)
{
	if (rotate(stack_b) == -1)
		return (-1);
	write(1, "rb\n", 3);
	return (0);
}

/*
perform rotation on both stack

int	rr(t_list **stack_a, t_list **stack_b)
{
	if (rotate(stack_a) == -1 || rotate(stack_b) == -1)
		return (-1);
	write(1, "rr\n", 3);
	return (0);
}
*/

int	rr(t_list **stack_a, t_list **stack_b)
{
	if ((ft_lstsize(*stack_a) < 2) || (ft_lstsize(*stack_b) < 2))
		return (-1);
	rotate(stack_a);
	rotate(stack_b);
	write(1, "rr\n", 3);
	return (0);
}
