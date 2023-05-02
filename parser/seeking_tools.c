/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   seeking_tools.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 17:49:10 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/05/01 14:52:24 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

int	find_pipe(int *arr, int max, int position)
{
	while (position <= max)
	{
		if (arr[position] == PIPE)
			return (position);
		position++;
	}
	return (position);
}

int	find_tokens(int val, t_tokens *list)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(list->content);
	if (!list->tokens)
		return (-1);
	while (list->tokens[i] != EOL && list->content[i])
	{
		if (list->tokens[i] == val)
			return (i);
		i++;
	}
	return (-1);
}

t_tokens	*find_args(t_tokens *list)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = list;
	while (list)
	{
		while (list->tokens[i] != EOL)
		{
			if (list->tokens[i] >= COMMAND)
				i = cut_to_args(list, i, list->tokens[i]);
			i++;
		}
		i = 0;
		list = list->next;
	}
	return (tmp);
}

// t_tokens *find_files(t_tokens *list)
// {
// 	t_tokens	*tmp;
// 	int			i;
// 	int			j;
// 	char		*filename;

// 	i = 0;
// 	tmp = list;
// 	while (list)
// 	{
// 		//while (list->content[i] && list->tokens[i] != EOL)
// 		while (list->tokens[i] != EOL)
// 		{
// 			if (list->tokens[i] >= REDIRECT_IP && list->tokens[i] <=
// 			REDIRECT_APPEND)
// 			{
// 				while (list->content[i] == '<' || list->content[i] == '>')
// 					i++;
// 				while (list->content[i] == ' ')
// 					i++;
// 				if (list->content[i])
// 					i = cut_to_files(list, i, list->tokens[i]);
// 			}
// 			else if (list->tokens[i] == RD_TIL_DELIM)
// 			{
// 				while (list->content[i] == '<' || list->content[i] == '>')
// 					i++;
// 				while (list->content[i] == ' ')
// 					i++;
// 				if (list->content[i])
// 				{
// 					i = cut_to_files(list, i, list->tokens[i]);
// 					j = ft_arrlen_c(list->files) - 1;
// 					filename = heredoc(list->files[j], 1);
// 					if (!filename)
// 					{
// 						list->files[j] = 0;
// 						list->mini_tok[j] = 0;
// 						tmp = 0;
// 						free_list(list);
// 						return (tmp);
// 					}
// 					list->files[j] = filename;
// 				}
// 			}
// 			i++;
// 		}
// 		i = 0;
// 		list = list->next;
// 	}
// 	return (tmp);
// }
// int	move_to_cut_point(t_tokens *list, int i)
// {
// 	while (list->content[i] == '<' || list->content[i] == '>')
// 		i++;
// 	while (list->content[i] == ' ')
// 		i++;
// 	return (i);
// }
// i = move_to_cut_point(list, i);

t_tokens	*find_files(t_tokens *list)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = list;
	while (list)
	{
		while (list->tokens[i] != EOL)
		{
			if (list->tokens[i] >= REDIRECT_IP && list->tokens[i] \
				<= REDIRECT_APPEND)
				i = cut_off_file_symbol(list, i);
			else if (list->tokens[i] == RD_TIL_DELIM)
			{
				i = cut_off_file_symbol(list, i);
				tmp = heredoc_func(list, tmp);
				if (!tmp)
					return (tmp);
			}
			i++;
		}
		i = 0;
		list = list->next;
	}
	return (tmp);
}

int	cut_off_file_symbol(t_tokens *list, int i)
{
	while (list->content[i] == '<' || list->content[i] == '>')
		i++;
	while (list->content[i] == ' ')
		i++;
	if (list->content[i])
		i = cut_to_files(list, i, list->tokens[i]);
	return (i);
}

// t_tokens	*cut_off_files_symbol_and_heredoc(t_tokens *list, int i, int j,
// t_tokens *tmp)
// {
// 	while (list->content[i] == '<' || list->content[i] == '>')
// 		i++;
// 	while (list->content[i] == ' ')
// 		i++;
// 	if (list->content[i])
// 	{
// 		i = cut_to_files(list, i, list->tokens[i]);
// 		return(heredoc_func(list, j, tmp));
// 	}
// 	return (tmp);
// }

t_tokens	*heredoc_func(t_tokens *list, t_tokens *tmp)
{
	char	*filename;
	int		j;

	j = ft_arrlen_c((list->files)) - 1;
	filename = heredoc(list->files[j], 1);
	if (!filename)
	{
		list->files[j] = 0;
		list->mini_tok[j] = 0;
		tmp = 0;
		free_list(list);
		return (tmp);
	}
	list->files[j] = filename;
	return (tmp);
}

int	*check_operators(char *input, int *arr)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!check_ampersand(input, arr, i))
			return (NULL);
		if (!check_or(input, arr, i))
			return (NULL);
		if (!check_pipes(input, arr, i))
			return (NULL);
		if (!check_r_arrow(input, arr, i))
			return (NULL);
		if (!check_l_arrow(input, arr, i))
			return (NULL);
		i++;
	}
	return (arr);
}
