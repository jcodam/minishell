/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   internal_splitters.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 12:49:19 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/05/02 16:33:05 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

// void	split_on_flags(t_tokens *list)
// {
// 	char		**temp;
// 	char		**dest;
// 	t_tokens	*tmp;
// 	int			j;
// 	int			i;

// 	tmp = list;
// 	dest = NULL;
// 	j = 0;
// 	i = 0;
// 	while (list)
// 	{
// 		while (list->args && list->args[i])
// 		{
// 			temp = split_quote(list->args[i], ' ');
// 			while (temp[j])
// 				dest = ft_arradd_index(dest, temp[j++], ft_arrlen_c(dest));
// 			free(temp);
// 			temp = 0;
// 			j = 0;
// 			i++;
// 		}
// 		i = 0;
// 		while (list->args[i])
// 		{
// 			free(list->args[i]);
// 		 	list->args[i] = 0;
// 			i++;
// 		}
// 		free (list->args);
// 		list->args = 0;
// 		list->args = dest;
// 		dest = 0;
// 		list = list->next;
// 	}
// }

static char	**cpy_arg_quote(t_tokens *list)
{
	char		**temp;
	char		**dest;
	int			j;
	int			i;

	dest = NULL;
	j = 0;
	i = 0;
	while (list->args && list->args[i])
	{
		temp = split_quote(list->args[i], ' ');
		while (temp[j])
			dest = ft_arradd_index(dest, temp[j++], ft_arrlen_c(dest));
		free(temp);
		temp = 0;
		j = 0;
		i++;
	}
	return (dest);
}

void	split_on_flags(t_tokens *list)
{
	char		**dest;
	t_tokens	*head;

	head = list;
	dest = NULL;
	while (list)
	{
		dest = cpy_arg_quote(list);
		ft_arrclear_c(list->args, ft_arrlen_c(list->args));
		list->args = dest;
		dest = 0;
		list = list->next;
	}
}


// void	split_on_flags(t_tokens *list)
// {
// 	char		**temp;
// 	char		**dest;
// 	t_tokens	*tmp;
// 	int			j;
// 	int			i;

// 	tmp = list;
// 	dest = 0;
// 	j = 0;
// 	i = 0;
// 	print_all_tokens(list);
// 	while (list)
// 	{
// 		while (list->args && list->args[i])
// 		{
// 			temp = split_quote(list->args[i], ' ');
// 			while (temp[j])
// 			{
// 				dest = ft_arradd_index(dest, temp[j], ft_arrlen_c(dest));
// 				j++;
// 			}
// 			free(temp);
// 			temp = 0;
// 			j = 0;
// 			i++;
// 		}
// 		i = 0;
// 		free_after_split(list, dest, i);
// 		list = list->next;
// 	}
// }

// void	free_after_split(t_tokens *list, char **dest, int i)
// {
// 	i = 0;
// 	while (list->args[i])
// 	{
// 		free(list->args[i]);
// 		list->args[i] = 0;
// 		i++;
// 	}
// 	free (list->args);
// 	list->args = 0;
// 	list->args = dest;
// 	dest = 0;
// }

// char	**arg_splitter(char **args, int i, int start, int end)
// {
// 	char	**tmp_args;
// 	int		current;
// 	int		j;

// 	j = 0;
// 	current = count_args(args);
// 	tmp_args = malloc(sizeof(char *) * (current + 2));
// 	while (j < i)
// 	{
// 		ft_strlcpy(tmp_args[j], args[j], (sizeof(args[j]) + 1));
// 		free(args[j]);
// 		j++;
// 	}
// 	start = 0;
// 	end = 0;
// 	tmp_args[j + 1] = ft_substr(args[i], start, end);
// 	tmp_args[j] = ft_substr(args[i], 0, (start - 1));
// 	tmp_args[j + 1] = mini_space_trimmer(tmp_args[j + 1]);
// 	tmp_args[j] = mini_space_trimmer(tmp_args[j]);
// 	j++;
// 	while (args[j])
// 	{
// 		ft_strlcpy(tmp_args[j + 1], args[j], (sizeof(args[j]) + 1));
// 		free(args[j]);
// 		j++;
// 	}
// 	tmp_args[j + 1] = 0;
// 	free_some_stuff(args);
// 	args = 0;
// 	return (tmp_args);
// }

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
		tmp_args[j] = ft_strdup(args[j]);
		//ft_strlcpy(tmp_args[j], args[j], (sizeof(args[j]) + 1));
		free(args[j]);
		j++;
	}
		//j = copy_and_free(tmp_args, args, j);
	start = 0;
	end = 0;
	tmp_args[j + 1] = ft_substr(args[i], start, end);
	tmp_args[j] = ft_substr(args[i], 0, (start - 1));
	tmp_args[j + 1] = mini_space_trimmer(tmp_args[j + 1]);
	tmp_args[j] = mini_space_trimmer(tmp_args[j]);
	j++;
	while (args[j])
	{
		tmp_args[j + 1] = ft_strdup(args[j]);
		//ft_strlcpy(tmp_args[j + 1], args[j], (sizeof(args[j]) + 1));
		free(args[j]);
		j++;
	}
		//j = copy_and_free(tmp_args, args, j);
	tmp_args[j + 1] = 0;
	free_some_stuff(args);
	args = 0;
	return (tmp_args);
}

int	copy_and_free(char **tmp_args, char **args, int j)
{
	ft_strlcpy(tmp_args[j + 1], args[j], (sizeof(args[j]) + 1));
	free(args[j]);
	j++;
	return (j);
}
