/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 17:50:32 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/03/02 17:38:17 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "all.h"

t_tokens	*new_node(char *input)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	new->content = input;
	new->next = 0;
	return (new);
}

