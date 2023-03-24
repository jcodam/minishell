/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_tools.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 18:27:02 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/03/23 14:55:11 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	*make_arr(int len)
{
	int	i;
	int	*arr;

	i = 0;
	arr = malloc(sizeof(int) * (len + 1));
	while (i < len)
	{
		arr[i] = -1;
		i++;
	}
	arr[i] = -2;
	return (arr);
}

void	print_array(int *arr)
{
	int	i;

	i = 0;
	while (arr[i] != -2)
	{
		ft_putnbr_fd(arr[i], 1);
		write(1, " ", 1);
		i++;
	}
}

void	ms_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*temp;

	temp = (*lst);
	if (!*lst)
		(*lst) = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

int	*label_spaces(char *input, int *arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (arr[i] == -1 && input[i] == ' ')
			arr[i] = 8;
		i++;
	}
	return (arr);
}

int	print_all_tokens(t_tokens *list)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = list;
	if (!list)
		return (0);
	while (tmp)
	{
		ft_putstr_fd("node content: ", 1);
		ft_putstr_fd("[", 1);
		ft_putstr_fd(tmp->content, 1);
		ft_putstr_fd("]", 1);
		ft_putstr_fd("\n", 1);
		if (tmp->tokens)
		{
			print_tokens(tmp->tokens);
			write(1, "\n", 1);
		}
		if (tmp->log_op)
		{
			ft_putnbr_fd(tmp->log_op, 1);
			ft_putstr_fd("\n", 1);
		}
		if (tmp->files)
		{
			while (tmp->files[i])
			{
				ft_putstr_fd("file: ", 1);
				ft_putstr_fd(tmp->files[i], 1);
				ft_putstr_fd("\n", 1);
				i++;
			}
		}
		i = 0;
		if (tmp->args)
		{
			while (tmp->args[i])
			{
				ft_putstr_fd("arg: ", 1);
				ft_putstr_fd(tmp->args[i], 1);
				ft_putstr_fd("\n", 1);
				i++;
			}
		}
		i = 0;
		if (tmp->mini_tok)
		{
			while (tmp->mini_tok[i])
			{
				ft_putstr_fd("val: ", 1);
				ft_putnbr_fd(tmp->mini_tok[i], 1);
				ft_putstr_fd("\n", 1);
			}
		}
		i = 0;
		tmp = tmp->next;
	}
	return (1);
}
