/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_list.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:38:40 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/03/24 19:42:39 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

int	get_node_length(int *arr, int start)
{
	int		temp;
	int		val;

	temp = start;
	val = arr[start];
	while (arr[start] == val)
		start++;
	return (start - temp);
}

t_tokens	*setup_new_node(t_tokens *top)
{
	t_tokens	*tmp;
	t_tokens	*old;

	tmp = malloc(sizeof(t_tokens));
	old = lst_end(top);
	old->next = tmp;
	tmp->args = 0;
	tmp->files = 0;
	tmp->tokens = 0;
	//tmp->iter = (old->iter + 1);
	return (tmp);
}

t_tokens	*lst_end(t_tokens *top)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = top;
	if (!top)
		return (0);
	while (tmp->next)
	{	
		i++;
		tmp = tmp->next;
	}
	return (tmp);
}

// int	get_index(t_tokens *top)
// {
// 	t_tokens	*tmp;

// 	tmp = top;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	return (tmp->iter + 1);
// }
