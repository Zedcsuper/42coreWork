/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:13:03 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/30 21:15:08 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
add a new node to the begining of list
*/

void	ft_lstadd_front(t_list **stack, t_list *new)
{
	new->next = *stack;
	*stack = new;
}
