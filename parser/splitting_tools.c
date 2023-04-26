/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting_tools.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 16:39:08 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/04/26 14:38:29 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

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

// needs freeing
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
	free_some_stuff(args);
	return (tmp_args);
}

void	free_some_stuff(char **args)
{
	int	j;

	j = 0;
	while (args[j])
	{
		free(args[j]);
		j++;
	}
	//this does not seem to do anything
	//j = 0;
	//while (tmp_args[j])
	//	j++;
	free (args);
}

void	fill_node_split(t_tokens *node, int split_point, int noc)
{
	char		*str;
	int			*arr;
	size_t		node_2_len;
	size_t		len;

	len = ft_strlen(node->content);
	node_2_len = (len - (split_point + noc) - 1);
	arr = node->tokens;
	str = node->content;
	node->next->content = ft_substr(str, (split_point + noc), \
	node_2_len);
	node->content = ft_substr(str, 0, (split_point - 1));
	node->next->tokens = ft_subarr(arr, (split_point + noc), \
	node_2_len);
	node->tokens = ft_subarr(arr, 0, (split_point - 1));
}

t_tokens	*check_for_commands(t_tokens *list)
{
	split_on_flags(list);
	return (list);
}
