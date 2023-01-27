/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 18:27:02 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/01/26 16:05:47 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
	Take input string
	tokanize values
	generate linked list with tokens
	output table map
*/

t_tokens	*tokanize(char *input)
{
	t_Commands	*val;
	t_tokens	*list;

	val = malloc(sizeof(val));
	list = init_list();
	tokanize_main(input, list);
	return (list);
}

t_tokens	*init_list(void)
{
	t_tokens	*top;

	top = malloc(sizeof(top));
	top->next = NULL;
	top->prev = NULL;
	top->start = 0;
	top->end = 0;
	top->content = NULL;
	return (top);
}

int	tokanize_main(char *input, t_tokens *list)
{
	int		i;
	int		j;
	char	*content;

	j = 0;
	i = 0;
	list->start = 0;
	while (input[i])
		i++;
	list->end = i;
	content = malloc(sizeof(i));
	if (!content)
		return (1);
	i = list->start;
	while (i < list->end)
	{
		content[j] = input[i];
		j++;
		i++;
	}
	list->content = content;
	//list->type = val[e_commands[OTHER]];
	return (0);
}

// t_tokens *hierarchy(t_tokense *list)
// {
// 	if ft_s
// }