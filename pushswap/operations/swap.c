/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:37:11 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/31 12:04:03 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
performs swap between first two elemnt on stack
and print sa , return -1 ifstack less than 2 elemnt
*/

static int	swap(t_list **stack)
{
	t_list	*head;
	t_list	*next;
	int		tmp_val;
	int		tmp_index;

	if (!*stack)
		error_message();
	if (ft_lstsize(*stack) < 2)
		return (-1);
	head = *stack;
	next = *stack;
	tmp_val = head->value;
	tmp_index = head->index;
	head->value = next->value;
	head->index = next->index;
	next->value = tmp_val;
	next->index = tmp_index;
	return (0);
}

/*
perform swap on stack a and print sa , return -1 if the stack less than 2
*/
int	sa(t_list **stack_a)
{
	if (swap(stack_a) == -1)
		return (-1);
	write(1, "sa\n", 3);
	return (0);
}

/*
performs swap on stack b and print sb,
return -1 if stack_b less than 2 elemnts
*/

int	sb(t_list **stack_b)
{
	if (swap(stack_b) == -1)
		return (-1);
	write(1, "sb\n", 3);
	return (0);
}

/*
perform sa and sb
*/
int	ss(t_list **stack_a, t_list **stack_b)
{
	if (swap(stack_a) == -1 || swap(stack_b) == -1)
		return (-1);
	write(1, "ss\n", 3);
	return (0);
}
