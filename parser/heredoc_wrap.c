/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_wrap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 12:22:20 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/05/15 16:16:09 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

t_tokens	*heredoc_func(t_tokens *list, t_tokens *tmp, t_super *env)
{
	char	*filename;
	int		j;

	j = ft_arrlen_c((list->files)) - 1;
	filename = heredoc(list->files[j], 1, env);
	if (j == -1)
	{
		free_list(tmp);
		return (tmp);
	}
	if (!filename)
	{
		list->files[j] = 0;
		list->mini_tok[j] = 0;
		free_list(tmp);
		tmp = 0;
		return (tmp);
	}
	list->files[j] = filename;
	return (tmp);
}
