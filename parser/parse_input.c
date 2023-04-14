/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:35:35 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/04/14 15:12:01 by avon-ben      ########   odam.nl         */
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
	//exit (0);
	list = check_for_commands(list);
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

t_tokens *check_for_commands(t_tokens *list)
{
	int			i;
	t_tokens	*tmp;

	tmp = list;
	i = 0;
	while (list)
	{
		if (list->mini_tok)
		{
			while (list->mini_tok[i] != -2)
			{
				if (list->mini_tok[i] == COMMAND)
					split_on_flags(list, i);
				else if (list->mini_tok[i] == FLAGS)
					split_between_flags(list, i);
				i++;
			}
		}
		i = 0;
		list = list->next;
	}
	return (tmp);
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
	&& list->mini_tok[start] != -2)
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
		printf("list->args[i]: %s,\tstart: %d,\tend: %d,\ti: %d\n", list->args[i], start, end, i);
		list->args = arg_splitter(list->args, i, start, end);
		update_mini_tok(list, i, FLAGS);
	}
}

void	split_on_flags(t_tokens *list, int i)
{
	int	end;
	int	start;

	start = 0;
	end = 0;
	while (list->args[i][start] != ' ' && list->args[i][start])
		start++;
	while (list->args[i][start] && list->args[i][start] != '-' \
	&& list->mini_tok[start] != -2)
		start++;
	if (list->args[i][start] == '-')
	{
		if (list->args[i][start + 1] == '-')
		{
			printf("syntax error");
			//exit (0);
		}
		end = start;
		while (list->args[i][end] != ' ' && list->args[i][end])
			end++;
		printf("list->args[i]: %s,\tstart: %d,\tend: %d,\ti: %d\n", list->args[i], start, end, i);
		list->args = arg_splitter(list->args, i, start, end);
		update_mini_tok(list, i, FLAGS);
	}
}

char	**arg_splitter(char **args, int i, int start, int end)
{
	char	**tmp_args;
	int		current;
	int		j;

	j = 0;
	current = count_args(args);
	tmp_args = malloc(sizeof(char *) * (current + 2));
	while (j < i)
	{
		ft_strlcpy(tmp_args[j], args[j], (sizeof(args[j]) + 1));
		j++;
	}
	tmp_args[j + 1] = ft_substr(args[i], start, end);
	tmp_args[j] = ft_substr(args[i], 0, (start - 1));
	tmp_args[j + 1] = mini_space_trimmer(tmp_args[j + 1]);
	tmp_args[j] = mini_space_trimmer(tmp_args[j]);
	j++;
	while (args[j])
	{
		ft_strlcpy(tmp_args[j + 1], args[j], (sizeof(args[j]) + 1));
		j++;
	}
	tmp_args[j + 1] = 0;
	j = 0;
	while (args[j])
	{
		free (args[j]);
		j++;
	}
	j = 0;
	while (tmp_args[j])
	{
		printf("tmp_args[%d], [%s]\n", j, tmp_args[j]);
		j++;
	}
	printf("tmp_args[%d], [%s]\n", j, tmp_args[j]);
	free (args);
	return (tmp_args);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	*mini_space_trimmer(char *string)
{
	int		start;
	int		end;
	char	*tmp;
	int		i;

	i = 0;
	start = 0;
	end = ft_strlen(string);
	//printf("start: %d", start);
	//printf("end: %d", end);
	while (string[start] == ' ')
		start++;
	while (string[end - 1] == ' ')
		end--;
	tmp = malloc(sizeof(char) * ((end - start) + 1));
	while (start < end)
	{
		tmp[i] = string[start];
		i++;
		start++;
	}
	tmp[i] = 0;
	free (string);
	return (tmp);
}

void update_mini_tok(t_tokens *list, int i, int val)
{
	int	len;
	int	*new;
	int	j;

	len = 0;
	j = 0;
	while (list->mini_tok[len] != -2)
		len++;
	new = malloc(sizeof(int) * (len + 2));
	while (j <= i)
	{
		new[j] = list->mini_tok[j];
		j++;
	}
	new[j] = val;
	while (list->mini_tok[j] != -2)
	{
		new[j + 1] = list->mini_tok[j];
		j++;
	}
	new[j + 1] = -2;
	free(list->mini_tok);
	list->mini_tok = new;
}
