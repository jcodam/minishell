/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cutting_tools.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 17:58:41 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/04/25 17:58:42 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

int	cut_to_args(t_tokens *list, int i, int val)
{
	int	length;
	int	start;

	(void)val;
	length = 0;
	start = i;
	while (list->tokens[i] >= COMMAND && list->tokens[i] != FILE_T)
	{
		length++;
		i++;
	}
	if (i > 0)
		i = i -1;
	if (!list->args)
		transpose_arg(list, length, start);
	else if (list->args)
		add_in_node_arg(list, length, start);
	return (i);
}

int	cut_to_files(t_tokens *list, int i, int val)
{
	int	length;
	int	start;

	length = 0;
	start = i;
	while (list->tokens[i] >= val && !ft_strchr("<>", list->content[i]))
	{
		length++;
		i++;
	}
	if (i > 0)
	{
		length = length - 1;
		i = i - 1;
	}
	if (!list->files)
		transpose_file(list, length, start, val);
	else if (list->files)
	{
		add_in_node_file(list, length, start);
		attach_token(list, start);
	}
	return (i);
}
