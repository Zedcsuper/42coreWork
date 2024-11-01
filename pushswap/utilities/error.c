/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:21:45 by zjamaien          #+#    #+#             */
/*   Updated: 2024/10/30 21:50:19 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

/*
prints an error message and terminates the program.
*/

void	error_message(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

/*
frees the memory allocated for a string array.
*/

void	free_string(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/* frees the memory allocated to stack represented by a linked list by freeing 
each node in the list and the list itself.
*/

void	free_stack(t_list **stack)
{
	t_list	*head;
	t_list	*tmp;

	head = *stack;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(stack);
}
