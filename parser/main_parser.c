/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:35:35 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/04/25 22:35:29 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

void		trim_spaces(t_tokens *list);
int			label_quotess(char *str, int *arr);

t_tokens	*main_loop(char *input)
{
	int			len;
	int			*arr;
	t_tokens	*list;

	len = ft_strlen(input);
	arr = make_arr(len);
	arr = tokanize(input, arr);
	if (!arr)
		return (NULL);
	list = malloc(sizeof(t_tokens));
	list->content = 0;
	list->next = 0;
	list = primary_split(input, arr, list);
	return (list);
}

int	*tokanize(char *input, int *arr)
{
	int	val;

	label_quotess(input, arr);
	while (arr)
	{
		arr = check_operators(input, arr);
		arr = command_after_pipe(input, arr);
		arr = label_spaces(input, arr);
		arr = check_commands(input, arr);
		val = check_empty_delims(input, arr);
		if (val)
		{
			syntax_err_message(val);
			return (NULL);
		}
		if (arr)
			return (arr);
	}
	return (NULL);
}

void	syntax_err_message(int val)
{
	if (val == 20)
		printf("syntax error near unexpected token `|'\n");
	else if (val == 21)
		printf("syntax error near unexpected token `&&'\n");
	else if (val == 22)
		printf("syntax error near unexpected token `||'\n");
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
	list = find_files(list);
	list = find_args(list);
	list = check_for_commands(list);
	return (list);
}

// splits the content of a node at the position given as 'split_points' and 
// places the righthand part of the string in a new node in the linked list.
// noc determines the amount of characters to be splitted on 
// (i.e. for '&&' noc would be 2)
// if node_nr is given, it determines the node in which the 
// string should be split
void	split_to_node(t_tokens *node, int split_point, int noc)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	new->content = 0;
	new->tokens = 0;
	new->args = 0;
	new->files = 0;
	new->mini_tok = 0;
	new->log_op = 0;
	if (node->next)
		new->next = node->next;
	else
		new->next = 0;
	node->next = new;
	fill_node_split(node, split_point, noc);
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

void	split_between_flags(t_tokens *list, int i)
{
	int	end;
	int	start;

	start = 0;
	end = 0;
	while (list->args[i][start] != ' ' && list->args[i][start])
		start++;
	while (list->args[i][start] && list->args[i][start] == ' ' \
	&& list->mini_tok[start] != EOL)
		start++;
	if (list->args[i][start] == '-')
	{
		if (list->args[i][start + 1] == '-')
		{
			printf("syntax error");
		}
		end = start;
		while (list->args[i][end] != ' ' && list->args[i][end])
			end++;
		list->args = arg_splitter(list->args, i, start, end);
		update_mini_tok(list, i, FLAGS);
	}
}

// memory leaks? 
void	split_on_flags(t_tokens *list)
{
	char		**temp;
	char		**temp1;
	t_tokens	*tmp;
	int			j;
	int			i;

	tmp = list;
	temp1 = NULL;
	j = 0;
	i = 0;
	while (list)
	{
		while (list->args && list->args[i])
		{
			temp = split_quote(list->args[i], ' ');
			while (temp[j])
				temp1 = ft_arradd_index(temp1, temp[j++], ft_arrlen_c(temp1));
				//j++;
			free(temp);
			temp = 0;
			j = 0;
			i++;
		}
		i = 0;
		list->args = temp1;
		temp1 = 0;
		list = list->next;
	}
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
