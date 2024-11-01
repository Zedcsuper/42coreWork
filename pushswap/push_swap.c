/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:05:35 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/01 17:04:04 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/push_swap.h"

	/*
		Initializes a stack by taking in arguments from the command line and
		creating a new node in the stack for each arguments. if the arguments
		is not provided from command line, it takes the arguments from the argv
		. finally, it assigin an index to each node in the stack and returns 
		the initialzed stack.
	*/
static void	init_stack(t_list **stack, int argc, char **argv)
{
	t_list	*new;
	char	**args;
	int		i;

	i = 0;
	if (argc == 2)
		args = ft_split(argv[1], ' ');
	else
	{
		i = 1;
		args = argv;
	}
	while (args[i])
	{
		new = ft_lstnew(ft_atoi(args[i]));
		ft_lstadd_back(stack, new);
		i++;
	}
	index_stack(stack);
	if (argc == 2)
		free_string(args);
}

	/*
		check the size of the input stack and uses either the simple sort or
		the radix sort algorithm to sort it. if the stack has 5 or fewer elemnt,
		it use the simple sort, otherwise uses radix sort.
	*/
static	void	sort_stack(t_list **stack_a, t_list **stack_b)
{
	if (ft_lstsize(*stack_a) <= 5)
		simple_sort(stack_a, stack_b);
	else
		radix_sort(stack_a, stack_b);
}

	/*
		Take integer input and sort them using a stack data structure.
		checks if there arae enough arguments, initialize the stack,
		sort them, and then free the memory used by the stack
	*/
int	main(int argc, char **argv)
{
	t_list	**stack_a;
	t_list	**stack_b;

	if (argc < 2)
		return (-1);
	check_args(argc, argv);
	stack_a = (t_list **)malloc(sizeof(t_list));
	*stack_a = NULL;
	init_stack(stack_a, argc, argv);
	if (is_sorted(stack_a) == 1)
	{
		free_stack(stack_a);
		exit (EXIT_SUCCESS);
	}
	stack_b = (t_list **)malloc(sizeof(t_list));
	*stack_b = NULL;
	sort_stack(stack_a, stack_b);
	free_stack(stack_a);
	free_stack(stack_b);
	return (0);
}
