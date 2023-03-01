/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokanize_tools.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:35:31 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/02/23 22:26:13 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	*command_after_pipe(char *input, int *arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (arr[i] == 7)
		{
			i++;
			while (input[i] != ' ')
			{
				arr[i] = 6;
				i++;
			}
		}
		i++;
	}
	return (arr);
}

void	*ms_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (void *) malloc(sizeof(size));
	if (ptr == NULL)
		return (NULL);
	while (i < size)
	{
		ptr[i] = nmemb;
		i++;
	}
	return (ptr);
}

int	*check_commands(char *input, int *arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (arr[i] == -1)
		{
			while (arr[i] == -1 || arr[i] == 8)
			{
				arr[i] = 6;
				i++;
			}
		}
		i++;
	}
	return (arr);
}

int	*check_operators(char *input, int *arr)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && arr[i] == -1)
		{
			if (!pipe_checker(input, i))
				return (NULL);
			arr[i] = 7;
		}
		if (input[i] == '>' && arr[i] == -1)
		{
			if (!red_op_checker(input, i))
				return (NULL);
			make_red_op(input, arr, i);
		}
		if (input[i] == '<' && arr[i] == -1)
		{
			if (!red_ip_checker(input, i))
				return (NULL);
			//error checker
			arr = make_red_ip(input, arr, i);
		}
			//arr[i] = 3;
		i++;
	}
	return (arr);
}

int	*make_red_op(char *input, int *arr, int i)
{
	int	done;
	int	val;

	done = 0;
	if (input[i + 1] == '>')
		val = 5;
	else
		val = 3;
	arr[i] = val;
	i++;
	if (val == 5)
		arr[i++] = val;
	while (done == 0)
	{
		while (input[i] == ' ')
			arr[i++] = val;
		while (input[i] != ' ' && arr[i] == -1)
			arr[i++] = val;
		done = 1;
	}
	return (arr);
}

int	*make_red_ip(char *input, int *arr, int i)
{
	int	done;
	int	val;

	done = 0;
	if (input[i + 1] == '<')
		val = 4;
	else
		val = 2;
	arr[i] = val;
	i++;
	if (val == 4)
		arr[i++] = val;
	while (done == 0)
	{
		while (input[i] == ' ')
			arr[i++] = val;
		while (input[i] != ' ' && arr[i] == -1)
			arr[i++] = val;
		done = 1;
	}
	return (arr);
}

int pipe_checker(char *input, int i)
{
	if (!input[i + 1])
	{
		write(1, "Minishell: syntax error near unexpected token `newline'", 56);
		return (0);
	}
	i++;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
	{
		write(1, "Minishell: syntax error near unexpected token `|'", 50);
		return (0);
	}
	return (1);
}

int red_op_checker(char *input, int i)
{
	if (!input[i + 1])
	{
		write(1, "Minishell: syntax error near unexpected token `newline'", 56);
		return (0);
	}
	i++;
	while (input[i] == ' ')
		i++;
	if (input[i] == '>')
	{
		write(1, "Minishell: syntax error near unexpected token `>'", 50);
		return (0);
	}
	return (1);
}

int red_ip_checker(char *input, int i)
{
	if (!input[i + 1])
	{
		write(1, "Minishell: syntax error near unexpected token `newline'", 56);
		return (0);
	}
	i++;
	while (input[i] == ' ')
		i++;
	if (input[i] == '>')
	{
		write(1, "Minishell: syntax error near unexpected token `<'", 50);
		return (0);
	}
	return (1);
}