/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_messaging.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 18:06:16 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/05/05 18:06:19 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

void	syntax_err_message(int val)
{
	if (val == 20 || val == 9)
		printf("syntax error near unexpected token `|'\n");
	else if (val == 21)
		printf("syntax error near unexpected token `&&'\n");
	else if (val == 22)
		printf("syntax error near unexpected token `||'\n");
}

void	write_relevant_message(char *input, int i)
{
	if (input[i + 1] == input[i])
	{
		write(2, "minishell: syntax error near unexpected token '", 48);
		write(2, &input[i], 1);
		write(2, &input[i], 1);
		write(2, "'\n", 2);
	}
	else
	{
		write(2, "minishell: syntax error near unexpected token '", 48);
		write(2, &input[i], 1);
		write(2, "'\n", 2);
	}
	g_exit_code = 258;
}
