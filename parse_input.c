/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:35:35 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/03/10 15:25:15 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_tokens	*main_loop(char *input)
{
	int			len;
	int			*arr;
	t_tokens	*list;

	list = malloc(sizeof(t_tokens));
	list->content = 0;
	list->next = 0;
	list->iter = 0;
	len = ft_strlen(input);
	arr = make_arr(len);
	arr = tokanize(input, arr);
	if (!arr)
		return (NULL);
	list = primary_split(input, arr, list);
	//list = split_into_list(input, arr, list);
	//split_args(list);
	return (list);
}

int	*tokanize(char *input, int *arr)
{
	while (arr)
	{
		arr = label_quotes(input, arr, 1);
		arr = label_quotes(input, arr, 0);
		arr = check_operators(input, arr);
		arr = command_after_pipe(input, arr);
		arr = label_spaces(input, arr);
		arr = check_commands(input, arr);
		if (arr)
			return (arr);
	}
	return (NULL);
}

int	find_pipe(int *arr, int max, int position)
{
	while (position <= max)
	{
		if (arr[position] == 7)
			return (position);
		position++;
	}
	return (position);
}

t_tokens	*split_into_list(char *input, int *arr, t_tokens *top)
{
	static int	start = 0;
	int			max;
	int			end;

	end = 0;
	max = ft_strlen(input);
	while (start < max)
	{
		end = (start + get_node_length(arr, start));
		if (start == 0)
			fill_node(top, input, start, end);
		else
			top = get_node(start, arr, input, top);
		if (start == end)
			start++;
		else
			start = end;
	}
	return (top);
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
	if (arr[start] != 8)
	{
		tmp = setup_new_node(top);
		str = ms_calloc(0, ((end - start) + 1));
		while (start < end)
		{
			str[i] = input[start];
			i++;
			start++;
		}
		str[i] = '\0';
		tmp->content = str;
		tmp->next = 0;
	}
	return (top);
}

int	*label_vals(int start, int end, int *arr, int sig)
{
	if (end != start)
	{
		while (start <= end)
		{
			arr[start] = sig;
			start++;
		}
	}
	return (arr);
}

// void	split_args(t_tokens *list)
// {
// 	if (!list)
// 		exit (0);
// 	while (list->next)
// 	{
// 		printf("node content: %s", list->content);
// 		mini_tokenizer(list);
// 		list = list->next;
// 	}
// }
