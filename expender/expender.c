/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expender.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 18:15:23 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/12 16:26:34 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

enum e_quote{
	no_quote = 0,
	DOUBLE_QUOTE,
	SINGLE_QUOTE
	};

int	strcmpindex(char *str, char c, int i)
{
	int	index;
	int	index2;

	index2 = 0;
	index = i;
	while (str[index])
	{
		if (str[index] == '"' && index2 == no_quote)
			index2 = DOUBLE_QUOTE;
		else if (str[index] == '"' && index2 == DOUBLE_QUOTE)
			index2 = no_quote;
		else if (str[index] == '\'' && index2 == no_quote)
			index2 = SINGLE_QUOTE;
		else if (str[index] == '\'' && index2 == SINGLE_QUOTE)
			index2 = no_quote;
		else if (str[index] == '$' && c == '$' && index2 < SINGLE_QUOTE)
			return (index);
		else if (str[index] == '*' && c == '*' && index2 < DOUBLE_QUOTE)
			return (index);
		index++;
	}
	return (-1);
}

char	*rep_exit_code(char *src, int index)
{
	char	*dest;
	char	*num;
	int		len;

	num = ft_itoa(g_exit_code);
	len = ft_strlen(num);
	len += ft_strlen(src);
	dest = malloc(len * sizeof(char));
	dest[len - 1] = '\0';
	len = 0;
	while (*src)
	{
		if (index == len)
		{
			src += 2;
			len += ft_strlcpy(&dest[len], num, ft_strlen(num) + 1);
		}
		else
		{
			dest[len] = *src;
			src++;
			len++;
		}
	}
	dest[len] = '\0';
	free(num);
	return (dest);
}

char	**arr_var(char **arr, char **env)
{
	int		index;
	int		index2;
	char	*var;

	index = 0;
	index2 = 0;
	while (arr[index])
	{
		index2 = strcmpindex(arr[index], '$', index2);
		if (index2 > -1 && arr[index][index2 + 1])
		{
			if (ft_isalnum(arr[index][index2 + 1]) || arr[index][index2 + 1] == '_')
			{
				var = ft_replacevar(arr[index], index2, env);
				arr = ft_arrdell_index(arr, index, ft_not_free);
				arr = ft_arradd_index(arr, var, index);
			}
			else if (arr[index][index2 + 1] == '?')
			{
				var = rep_exit_code(arr[index], index2);
				free(arr[index]);
				arr[index] = var;
			}
			index2++;
		}
		else
		{
			index2 = 0;
			index++;
		}
	}
	return (arr);
}

char	**arr_wildcard(char **arr)
{
	int		index;
	int		index2;
	t_list	*head;
	t_list	*list;

	index = 0;
	index2 = 0;
	while (arr[index])
	{
		index2 = strcmpindex(arr[index], '*', 0);
		if (index2 > -1)
		{
			head = get_wildcard(arr[index]);
			list = head;
			arr = ft_arrdell_index(arr, index, free);
			index2 = index;
			while (list)
			{
				arr = ft_arradd_index(arr, list->content, index);
				list = list->next;
				index++;
			}
			index--;
			ft_lstclear(&head, ft_not_free);
		}
		index++;
	}
	return (arr);
}

int	arr_quotes_int(char *str)
{
	int	index;
	int	index2;
	int	index3;

	index3 = 0;
	index2 = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == '"' && index2 == no_quote)
			index2 = DOUBLE_QUOTE;
		else if (str[index] == '"' && index2 == DOUBLE_QUOTE)
			index2 = no_quote;
		else if (str[index] == '\'' && index2 == no_quote)
			index2 = SINGLE_QUOTE;
		else if (str[index] == '\'' && index2 == SINGLE_QUOTE)
			index2 = no_quote;
		else
			index3++;
		index++;
	}
	return (index3);
}

char	*arr_quotes2(char *str)
{
	int		index;
	int		index2;
	int		index3;
	char	*dest;

	dest = malloc((arr_quotes_int(str) + 1) * sizeof(char));
	index3 = 0;
	index2 = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == '"' && index2 == no_quote)
			index2 = DOUBLE_QUOTE;
		else if (str[index] == '"' && index2 == DOUBLE_QUOTE)
			index2 = no_quote;
		else if (str[index] == '\'' && index2 == no_quote)
			index2 = SINGLE_QUOTE;
		else if (str[index] == '\'' && index2 == SINGLE_QUOTE)
			index2 = no_quote;
		else
		{
			dest[index3] = str[index];
			index3++;
		}
		index++;
	}
	dest[index3] = '\0';
	return (dest);
}

char	**arr_quotes(char **arr)
{
	int		index;
	int		index2;
	char	*temp;

	index2 = 0;
	index = 0;
	while (arr[index])
	{
		if (ft_strchr(arr[index], '\''))
			index2 = 1;
		if (ft_strchr(arr[index], '"'))
			index2 = 1;
		if (index2)
		{
			temp = arr_quotes2(arr[index]);
			arr = ft_arrdell_index(arr, index, free);
			arr = ft_arradd_index(arr, temp, index);
		}
		index2 = 0;
		index++;
	}
	return (arr);
}

char	**arr_expander(char **arr, char **env)
{
	arr = arr_var(arr, env);
	ft_putendl_fd("var complete", 1);
	arr = arr_wildcard(arr);
	ft_putendl_fd("wildcard complete", 1);
	arr = arr_quotes(arr);
	ft_putendl_fd("quote complete", 1);
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

// int main(int argc, char const *argv[])
// {
// 	t_list *head;
// 	if (argc == 2)
// 	{
// 		head = get_wildcard((char *)(argv[1]));
// 		ft_lstputs_fd(head, 1);
// 	}
// 	return 0;
// }

// int	main(int argc, char *argv[])
// {
// 	t_list	*card;

// 	if (argc != 2)
// 	{
// 		ft_putnbr_fd(argc, 1);
// 		for (int i = 0; i < argc ; i++)
// 			ft_putendl_fd(argv[i], 1);
// 		return 0;
// 	}
// 	card = get_wildcard("e*");
// 	system("leaks -q a.out");
// 	while (card)
// 	{
// 		ft_putstr_fd(card->content, 1);
// 		ft_putchar_fd(' ', 1);
// 		card = card->next;
// 	}
// 	ft_putchar_fd('\n', 1);
// 	// free(card);
// 	return 0;
// }
