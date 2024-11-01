/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:56:30 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/01 17:06:16 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
this function callculate the distance between a given
index and the head of a linked list
*/

int	index_distance_head(t_list **stack, int index)
{
	t_list	*head;
	int		distance;

	distance = 0;
	head = *stack;
	while (head)
	{
		if (head->index == index)
			break ;
		distance++;
		head = head->next;
	}
	return (distance);
}

/*
find and returns the minimum value in a linked list
exluding a given value.
*/
int	get_min(t_list **stack, int val)
{
	t_list	*head;
	int		min;

	head = *stack;
	min = head->index;
	while (head->next)
	{
		head = head->next;
		if ((head->index < min) && head->index != val)
			min = head->index;
	}
	return (min);
}

/*
searches for next minimum value in a stack, represented as a linked list
it return a pointer to the node that contains the minimum value.
*/
static t_list	*get_next_min(t_list **stack)
{
	t_list	*head;
	t_list	*min;
	int		has_min;

	min = NULL;
	has_min = 0;
	head = *stack;
	while (head)
	{
		if ((head->index == -1) && (!has_min || head->value < min->value))
		{
			min = head;
			has_min = 1;
		}
		head = head->next;
	}
	return (min);
}

/*
assign an index to each elemnt of a linked list
stack in ascending order based on their value.
*/
void	index_stack(t_list **stack)
{
	t_list	*head;
	int		index;

	index = 0;
	head = get_next_min(stack);
	while (head)
	{
		head->index = index++;
		head = get_next_min(stack);
	}
}

/*
check if a stack is sorted in ascending order.
it takes a pointer to the top of the stack and returns an 
integer : 1 if the stack is sorted else : 0
*/
int	is_sorted(t_list **stack)
{
	t_list	*head;

	head = *stack;
	while (head && head->next)
	{
		if (head->value > head->next->value)
			return (0);
		head = head->next;
	}
	return (1);
}
