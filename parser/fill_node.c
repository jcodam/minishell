/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_node.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:47:26 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/05/02 12:35:08 by avon-ben      ########   odam.nl         */
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
}

t_tokens	*get_node(int start, int *arr, char *input, t_tokens *top)
{
	int			end;
	char		*str;
	int			i;
	t_tokens	*tmp;

	i = 0;
	end = start;
	while (arr[end] == arr[start])
		end++;
	if (arr[start] != SPC)
	{
		tmp = setup_new_node(top);
		str = ms_calloc(0, ((end - start) + 1));
		while (start < end)
			str[i++] = input[start++];
		str[i] = '\0';
		tmp->content = str;
		tmp->next = 0;
	}
	return (top);
}