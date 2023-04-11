/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:35:35 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/04/11 16:51:01 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

void		trim_spaces(t_tokens *list);

void	print_list(t_tokens *list)
{
	while (list != NULL)
	{
		printf("%s\t[%s]\n", __func__, list->content);
		list = list->next;
	}
}

t_tokens	*primary_split(char *input, int *arr, t_tokens *list)
{
	list->content = input;
	list->tokens = arr;
	list->log_op = 1;
	list->args = 0;
	list->files = 0;
	list->mini_tok = 0;
	list = split_on_amps(list);
	list = split_on_or(list);
	list = split_on_pipes(list);
	trim_spaces(list);
	list = find_docs(list);
	list = find_args(list);
	//list = check_for_commands(list);
	return (list);
}

t_tokens	*main_loop(char *input)
{
	int			len;
	int			*arr;
	t_tokens	*list;

	list = malloc(sizeof(t_tokens));
	list->content = 0;
	list->next = 0;
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
		//arr = revert_quotes(input, arr);
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

// t_tokens *check_for_commands(t_tokens *list)
// {
// 	int			i;
// 	t_tokens	*tmp;

// 	i = 0;
// 	while (list)
// 	{
// 		if (list->mini_tok)
// 		{
// 			while (list->mini_tok[i] != -2)
// 			{
// 				if (list->mini_tok[i] == COMMAND)
// 					split_on_flags(list, i);
// 				i++;
// 			}
// 		}
// 	}
// }

// void	split_on_flags(t_tokens *list, int i)
// {
// 	int	end;
// 	int	start;

// 	start = 0;
// 	while (list->args[i][start] != ' ')
// 		start++;
// 	while (list->args[i][start] != '-' && list->mini_tok[start] != -2)
// 		start++;
// 	if (list->args[i][start] == '-')
// 	{
// 		end = start;
// 		while (list->args[i][end] != " " && list->args[i][end] != '-' && \
// 		list->args[i][end])
// 			end++;
// 	}
// 	if (list->args[i + 1])
	



	
// }

// void	arg_splitter(char **args, int i, int start, int end)
// {
// 	char	**tmp_args;
// 	int		j;

// 	j = 0;
// 	while (list->args[j])
// 		j++;
// 	// tmp_args = malloc(sizeof(char *) * (j + 2));
// 	// j = 0;
// 	// while (list->args[j])
// 	// {
// 	// 	ft_strlcpy(tmp_args[j], list->args[j], ft_strlen(list->args[j]));
// 	// 	j++;
// 	// }
// 	// tmp_args[j] = ft_substr(list->content, i, length);
// 	// tmp_args[j + 1] = 0;
// 	// j = 0;
// 	// while (list->args[j])
// 	// {
// 	// 	free (list->args[j]);
// 	// 	j++;
// 	// }
// 	// free (list->files);
// 	// list->args = tmp_args;
// }