/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_node.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:47:26 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/03/24 17:08:27 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

void	fill_node(t_tokens *node, char *input, int start, int end)
{
	char	*string;
	int		i;

	i = 0;
	string = malloc((end - start) + 1);
	while (start < end)
	{
		string[i] = input[start];
		i++;
		start++;
	}
	string[i] = '\0';
	node->content = string;
	node->iter = 0;
}

