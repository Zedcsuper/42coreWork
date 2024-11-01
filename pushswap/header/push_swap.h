/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:28:32 by zjamaien          #+#    #+#             */
/*   Updated: 2024/11/01 16:53:02 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* LIBRARY */
# include <unistd.h> // write
# include <stdlib.h> //malloc
# include <limits.h> //INIT_MIN & INT_MAX

/* STRUCTURE
	value: an integer value
	index: an integer index
	next: a pointer to the next node in the linked list
*/

/* struct called s_list, whicj is aliased as t_list */
typedef struct s_list
{
	int				value;
	int				index;
	struct s_list	*next;
}	t_list;

/* list functions */
t_list	*ft_lstnew(int value);
t_list	*ft_lstlast(t_list *head);
void	ft_lstadd_front(t_list **stack, t_list *new_e);
void	ft_lstadd_back(t_list **stack, t_list *new_e);
int		ft_lstsize(t_list *head);
/* libft function */
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
long	ft_atoi(const char *str);
int		ft_isdigit(int c);
/* utilities */
void	free_string(char **str);
void	free_stack(t_list **stack);
void	index_stack(t_list **stack);
int		get_min(t_list **stack, int val);
/* validation */
void	error_message(void);
void	check_args(int argc, char **argv);
int		is_sorted(t_list **stack);
/* sort operation */
int		pa(t_list **stack_a, t_list **stack_b);
int		pb(t_list **stack_a, t_list **stack_b);
int		sa(t_list **stack_a);
int		sb(t_list **stack_b);
int		ss(t_list **stack_a, t_list **stack_b);
int		ra(t_list **stack_a);
int		rb(t_list **stack_b);
int		rr(t_list **stack_a, t_list **stack_b);
int		rra(t_list **stack_a);
int		rrb(t_list **stack_b);
int		rrr(t_list **stack_a, t_list **stack_b);
int		index_distance_head(t_list **stack, int index);
/* algorithims */
void	sort_3(t_list **stack_a);
void	sort_4(t_list **stack_a, t_list **stack_b);
void	sort_5(t_list **stack_a, t_list **stack_b);
void	simple_sort(t_list **stack_a, t_list **stack_b);
void	radix_sort(t_list **stack_a, t_list **stack_b);

#endif
