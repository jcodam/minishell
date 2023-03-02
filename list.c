/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 17:50:32 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/03/01 19:39:08 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "all.h"

// void	add_node_end(char *input, t_tokens *top)
// {
// 	t_tokens	*cpy;

// 	cpy = top;
// 	if (!top)
// 		return ;
// 	while (cpy->next)
// 		cpy = cpy->next;
// 	cpy->next = new_node(input, cpy);
// }

t_tokens	*new_node(char *input)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	new->content = input;
	new->next = 0;
	return (new);
}

