/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 18:15:23 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/17 19:53:13 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"
#include "../headers/quotedef.h"

char	**expend_quotes(char **arr);
char	**expend_vars(char **arr, char **env);

int	strcmpindex(char *str, char c, int i)
{
	int	index;
	int	quote_mark;

	quote_mark = 0;
	index = i;
	while (str[index])
	{
		if (str[index] == '"' && quote_mark == NO_QUOTE)
			quote_mark = DOUBLE_QUOTE;
		else if (str[index] == '"' && quote_mark == DOUBLE_QUOTE)
			quote_mark = NO_QUOTE;
		else if (str[index] == '\'' && quote_mark == NO_QUOTE)
			quote_mark = SINGLE_QUOTE;
		else if (str[index] == '\'' && quote_mark == SINGLE_QUOTE)
			quote_mark = NO_QUOTE;
		else if (str[index] == '$' && c == '$' && quote_mark < SINGLE_QUOTE)
			return (index);
		else if (str[index] == '*' && c == '*' && quote_mark < DOUBLE_QUOTE)
			return (index);
		index++;
	}
	return (-1);
}

static char	**add_list_to_arr(t_list *list, char **arr, int *index)
{
	while (list)
	{
		arr = ft_arradd_index(arr, list->content, *index);
		list = list->next;
		*index += 1;
	}
	return (arr);
}

static char	**expand_wildcard(char **arr)
{
	int		index;
	int		has_wildcard;
	t_list	*head;

	index = 0;
	has_wildcard = 0;
	while (arr[index])
	{
		has_wildcard = strcmpindex(arr[index], '*', 0);
		if (has_wildcard > -1)
		{
			head = get_wildcard(arr[index]);
			arr = ft_arrdell_index(arr, index, free);
			arr = add_list_to_arr(head, arr, &index);
			index--;
			ft_lstclear(&head, ft_not_free);
		}
		index++;
	}
	return (arr);
}

char	**arr_expander(char **arr, char **env)
{
	if (!arr || !*arr)
		return (arr);
	arr = expend_vars(arr, env);
	arr = expand_wildcard(arr);
	arr = expend_quotes(arr);
	return (arr);
}

// void	ex(void)
// {
// 	system("leaks -q a.out");
// }

// int main(int argc, char const *argv[], char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	char **arr;
// 	char **env;
// 	char *line;
// 	int i = 0;
// 	// t_list *head = NULL;
// 	// atexit(ex);
// 	// head = get_wildcard("e*");
// 	// ft_lstputs_fd(head->next, 1);
// 	g_exit_code = 42;
// 	arr = malloc(1 * sizeof(char *));
// 	arr[0] = 0;
// 	env = ft_arrdup_c(envp, ft_arrlen_c(envp));
// 	while (i < 3)
// 	{
// 		line = read_the_line();
// 		arr = ft_arradd_index(arr, line, i);
// 		i++;
// 	}
// 	ft_putarrs_fd(arr, 1);
// 	arr = arr_expander(arr, env);
// 	ft_putarrs_fd(arr, 1);
// 	ft_arrclear_c(arr, ft_arrlen_c(arr));
// 	ft_arrclear_c(env, ft_arrlen_c(env));
// 	// system("leaks -q a.out");
// 	return 0;
// }
