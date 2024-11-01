/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:49:29 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/31 20:07:53 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
calculate the number of bits required to represnt the
largest elemnt in a stack of integers. it tackes a pointer
to a pointer to a list structure and return the number of bits as int
*/

static int	get_max_bits(t_list **stack)
{
	t_list	*head;
	int		max;
	int		max_bits;

	head = *stack;
	max = head->index;
	max_bits = 0;
	while (head)
	{
		if (head->index > max)
			max = head->index;
		head = head->next;
	}
	while ((max >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

/*
function takes two pointers to t_list structure
as input and sort the stack using radix sort algorithim. it first
detrmine the maxmum number of bits needed to represent the largest
elemnt in the stack, then iterate throgh each bits position and perform bucket
sorting based on that position. finally, it assemble the sorted stack by
repetedly push back to stack_a
*/
void	radix_sort(t_list **stack_a, t_list **stack_b)
{
	t_list	*head_a;
	int		i;
	int		j;
	int		size;
	int		max_bits;

	i = 0;
	head_a = *stack_a;
	size = ft_lstsize(head_a);
	max_bits = get_max_bits(stack_a);
	while (i < max_bits)
	{
		j = 0;
		while (j++ < size)
		{
			head_a = *stack_a;
			if (((head_a->index >> i) & 1) == 1)
				ra(stack_a);
			else
				pb(stack_a, stack_b);
		}
		while (ft_lstsize(*stack_b) != 0)
			pa(stack_a, stack_b);
		i++;
	}
}
