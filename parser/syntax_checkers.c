/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_checkers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 18:54:10 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/04/25 16:15:04 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

int	red_op_checker(char *input, int i)
{
	if (!input[i + 1])
	{
		write(2, "Minishell: syntax error near unexpected token `newline'\n", \
		56);
		g_exit_code = 258;
		return (0);
	}
	i++;
	while (ft_iswhite_space(input[i]))
		i++;
	if (ft_strrchr("|&", input[i]))
	{
		if (input[i + 1] == '|' && input[i] == '|')
			printf("Minishell: syntax error near unexpected token `||'\n");
		else
			printf("Minishell: syntax error near unexpected token `%c'\n", \
			input[i]);
		g_exit_code = 258;
		return (0);
	}
	if (input[i] == '>' && input[i + 1] == '>')
	{
		write(2, "Minishell: syntax error near unexpected token `>'\n", 50);
		g_exit_code = 258;
		return (0);
	}
	return (1);
}

int	red_ip_checker(char *input, int i)
{
	if (!input[i + 1])
	{
		write(2, "Minishell: syntax error near unexpected token `newline'\n", \
		56);
		g_exit_code = 258;
		return (0);
	}
	i++;
	while (ft_iswhite_space(input[i]))
		i++;
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			write(2, "Minishell: syntax error near unexpected token `<'\n", 50);
			g_exit_code = 258;
			return (0);
		}
	}
	return (1);
}

int	pipe_checker(char *input, int i)
{
	if (!input[i + 1] || !is_empty(&input[i + 1]))
	{
		write(2, "Minishell: syntax error near unexpected token `newline'\n", \
		56);
		g_exit_code = 258;
		return (0);
	}
	i++;
	while (ft_iswhite_space(input[i]))
		i++;
	if (ft_strrchr("|&", input[i]))
	{
		if (input[i + 1] == '|' && input[i] == '|')
			printf("Minishell: syntax error near unexpected token `||'\n");
		else
			printf("Minishell: syntax error near unexpected token `%c'\n", \
			input[i]);
		g_exit_code = 258;
		return (0);
	}
	return (1);
}

int	OR_error_checker(char *input, int i)
{
	if ((input[i + 2] == '|') || !content_before(input, i))
	{
		write(2, "minishell: syntax error near unexpected token `||'\n", 51);
		g_exit_code = 258;
		return (0);
	}
	return (1);
}

int	amp_checker(char *input, int i)
{
	if (input[i + 2] == '&' || !content_before(input, i))
	{
		write(2, "minishell: syntax error near unexpected token `&&'\n", 51);
		g_exit_code = 258;
		return (0);
	}
	return (1);
}
