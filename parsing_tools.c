/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_tools.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 18:27:02 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/03/10 14:47:30 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	*make_arr(int len)
{
	int	i;
	int	*arr;

	i = 0;
	arr = malloc(sizeof(int) * len);
	while (i <= len)
	{
		arr[i] = -1;
		i++;
	}
	arr[len] = -2;
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

	tmp = list;
	if (!list)
		return (0);
	while (tmp->content)
	{
		ft_putstr_fd("node value: ", 1);
		ft_putnbr_fd(tmp->iter, 1);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("node content: ", 1);
		ft_putstr_fd("[", 1);
		ft_putstr_fd(tmp->content, 1);
		ft_putstr_fd("]", 1);
		ft_putstr_fd("\n", 1);
		print_tokens(tmp->tokens);
		write(1, "\n", 1);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (1);
}
