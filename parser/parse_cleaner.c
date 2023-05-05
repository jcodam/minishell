/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cleaner.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 17:53:35 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/05/05 16:56:29 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

void	trim_spaces(t_tokens *list)
{
	int		start;
	int		end;
	char	*tmp;
	int		*arr;

	while (list)
	{
		arr = list->tokens;
		tmp = list->content;
		start = 0;
		end = ((ft_strlen(list->content)) - 1);
		while (list->content[start] == ' ')
			start++;
		if (end < start)
			end = (start + 1);
		while (list->content[end] == ' ' && end >= (start + 1))
			end--;
		list->content = ft_substr(tmp, start, (end - start));
		list->tokens = ft_subarr(arr, start, (end - start));
		if (!list->tokens)
			free(list->tokens);
		if (!list->content)
			free(list->content);
		free(arr);
		free(tmp);
		list = list->next;
	}
}

char	*mini_space_trimmer(char *string)
{
	int		start;
	int		end;
	char	*tmp;
	int		i;

	i = 0;
	start = 0;
	end = (ft_strlen(string) - 1);
	while (string[start] == ' ')
		start++;
	if (end < start)
		end = (start + 1);
	while (string[end] == ' ' && end > start)
		end--;
	// while (string[end] == ' ')
	// 	end--;
	//printf("malloc size: %d\n", ((end - start) + 1));
	tmp = malloc(sizeof(char) * ((end - start) + 1));
	while (start < end)
	{
		tmp[i] = string[start];
		i++;
		start++;
	}
	tmp[i] = '\0';
	free (string);
	return (tmp);
}

int	check_empty_delims(char *input, int *arr)
{
	int	i;
	int	set;

	set = 0;
	i = 0;
	while (arr[i] != EOL)
	{
		while ((arr[i] < PIPE || arr[i] > SPLIT_OR) && arr[i] != EOL)
			i++;
		if (arr[i] >= PIPE && arr[i] <= SPLIT_OR)
		{
			i++;
			if (arr[i] == SPLIT_AND || arr[i] == SPLIT_OR)
				i++;
			while ((arr[i] < PIPE || arr[i] > SPLIT_OR) && arr[i] != EOL)
				if (!ft_iswhite_space(input[i++]))
					set = 1;
			if (!set)
				return (arr[i]);
			set = 0;
		}
	}
	return (0);
}
