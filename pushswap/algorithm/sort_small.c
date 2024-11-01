/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:17:06 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/31 22:29:32 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
the onle three casse to sort_3
*/
static void	sort_132(t_list	**stack_a)
{
	ra(stack_a);
	sa(stack_a);
	rra(stack_a);
}

static void	sort_231(t_list **stack_a, t_list *head, int min)
{
	if (head->next->index == min)
		sa(stack_a);
	else
		rra(stack_a);
}

static void	sort_312(t_list **stack_a, t_list *head, int min)
{
	if (head->next->index == min)
		ra(stack_a);
	else
	{
		sa(stack_a);
		rra(stack_a);
	}
}

/*
sort a stack of three numbers by selecting the appropriate sorting
*/

void	sort_3(t_list **stack_a)
{
	t_list	*head;
	int		min;
	int		next_min;

	head = *stack_a;
	min = get_min(stack_a, -1);
	next_min = get_min(stack_a, min);
	if (is_sorted(stack_a) == 1)
		return ;
	if (head->index == min && head->next->index != next_min)
		sort_132(stack_a);
	else if (head->index == next_min)
		sort_231(stack_a, head, min);
	else
		sort_312(stack_a, head, min);
}
