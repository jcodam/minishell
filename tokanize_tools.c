/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokanize_tools.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:35:31 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/02/20 16:19:56 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	*command_after_pipe(char *input, int *arr)
{
	int	i;

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
			arr[i] = 7;
		if (input[i] == '>' && arr[i] == -1)
			arr[i] = 4;
		if (input[i] == '<' && arr[i] == -1)
			arr[i] = 3;
		i++;
	}
	return (arr);
}
