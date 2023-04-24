/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_splitter.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 18:49:19 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/04/24 14:07:13 by avon-ben      ########   odam.nl         */
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
		if (end < 0)
			end = 0;
		while (list->content[start] == ' ')
			start++;
		while (list->content[end] == ' ')
			end--;
		list->content = ft_substr(tmp, start, (end - start));
		list->tokens = ft_subarr(arr, start, (end - start));
		free(arr);
		free(tmp);
		list = list->next;
	}
}

t_tokens	*split_on_amps(t_tokens *list)
{
	t_tokens	*top;
	int			place;

	if (!list)
		return (NULL);
	top = list;
	place = 0;
	while (list)
	{
		place = find_tokens(SPLIT_AND, list);
		if (place == -1)
			break ;
		split_to_node(list, place, 2);
		list->next->log_op = OPP_AND;
		list = list->next;
	}
	return (top);
}

t_tokens	*split_on_or(t_tokens *list)
{
	t_tokens	*top;
	int			place;

	if (!list)
		return (NULL);
	top = list;
	place = -1;
	while (list)
	{
		place = find_tokens(SPLIT_OR, list);
		if (place != -1)
		{
			split_to_node(list, place, 2);
			list->next->log_op = OPP_OR;
		}
		list = list->next;
	}
	return (top);
}

t_tokens	*split_on_pipes(t_tokens *list)
{
	t_tokens	*top;
	int			place;

	if (!list)
		return (NULL);
	top = list;
	place = -1;
	while (list)
	{
		place = find_tokens(PIPE, list);
		if (place != -1)
		{
			split_to_node(list, place, 1);
			list->next->log_op = OPP_PIPE;
		}
		list = list->next;
	}
	return (top);
}

int	find_tokens(int val, t_tokens *list)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(list->content);
	if (!list->tokens)
		return (-1);
	while (list->tokens[i] != EOL && list->content[i])
	{
		if (list->tokens[i] == val)
			return (i);
		i++;
	}
	return (-1);
}

// splits the content of a node at the position given as 'split_points' and 
// places the righthand part of the string in a new node in the linked list.
// noc determines the amount of characters to be splitted on 
// (i.e. for '&&' noc would be 2)
// if node_nr is given, it determines the node in which the 
// string should be split
void	split_to_node(t_tokens *node, int split_point, int noc)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	new->content = 0;
	new->tokens = 0;
	new->args = 0;
	new->files = 0;
	new->mini_tok = 0;
	new->log_op = 0;
	if (node->next)
		new->next = node->next;
	else
		new->next = 0;
	node->next = new;
	fill_node_split(node, split_point, noc);
}

void	fill_node_split(t_tokens *node, int split_point, int noc)
{
	char		*str;
	int			*arr;
	size_t		node_2_len;
	size_t		len;

	len = ft_strlen(node->content);
	node_2_len = (len - (split_point + noc) - 1);
	arr = node->tokens;
	str = node->content;
	node->next->content = ft_substr(str, (split_point + noc), \
	node_2_len);
	node->content = ft_substr(str, 0, (split_point - 1));
	node->next->tokens = ft_subarr(arr, (split_point + noc), \
	node_2_len);
	node->tokens = ft_subarr(arr, 0, (split_point - 1));
}

int *ms_arrdup(int *arr, int len)
{
	int	*newarr;
	int	i;

	i = 0;
	if (!arr || !len)
		return (NULL);
	newarr = malloc(sizeof(int) * len);
	while (i <= len)
	{
		newarr[i] = arr[i];
		i++;
	}
	newarr[i] = -2;
	return (newarr);
}

int	*calloc_array(int len, int type)
{
	int	*ret;
	int	i;

	i = 0;
	if (!len || !type)
		return (NULL);
	ret = malloc((len + 1) * sizeof(type));
	while (i <= len)
	{
		ret[i] = -2;
		i++;
	}
	return (ret);
}

int	*ft_subarr(int *arr, size_t start, size_t len)
{
	size_t			i;
	int				*newarr;
	size_t			arrlen;

	i = 0;
	if (!arr)
		return (0);
	arrlen = ar_len(arr);
	if (start > arrlen)
		return (0);
	newarr = calloc_array((len + 2), -2);
	if (!newarr)
	{
		printf("\n malloc error!\n");
		return (NULL);
	}
	while (i <= len)
	{
		newarr[i] = arr[start + i];
		i++;
	}
	newarr[i] = -2;
	return (newarr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*newstr;
	size_t			strlen;

	i = 0;
	if (s == 0)
		return (NULL);
	strlen = ft_strlen(s);
	if (start > strlen)
		return (ft_strdup(""));
	if (len > strlen - start)
		return (ft_strdup(s + start));
	newstr = (char *)malloc(len + 2);
	if (newstr == 0)
	{
		printf("\n malloc error!\n");
		return (NULL);
	}
	while (i <= len)
	{
		newstr[i] = s[start + i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

void print_tokens(int *arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != -2)
	{
		ft_putnbr_fd(arr[i], 1);
		write(1, " ", 1);
		i++;
	}
	ft_putnbr_fd(arr[i], 1);
	ft_putstr_fd("]", 1);
}

int	ar_len(int *arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (0);
	while (arr[len] != -2)
		len++;
	return (len);
}

t_tokens *find_args(t_tokens *list)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = list;
	while (list)
	{
		//while (list->content[i] && (list->tokens[i] != EOL))
		//while(list->content[i])
		while (list->tokens[i] != EOL)
		{
			if (list->tokens[i] >= COMMAND)
				i = cut_to_args(list, i, list->tokens[i]);
			i++;
		}
		i = 0;
		list = list->next;
	}
	return (tmp);
}

int	cut_to_args(t_tokens *list, int i, int val)
{
	int	length;
	int	start;

	(void)val;
	length = 0;
	start = i;
	while (list->tokens[i] >= COMMAND && list->tokens[i] != FILE_T)
	{
		length++;
		i++;
	}
	if (i > 0)
		i = i -1;
	if (!list->args)
		transpose_arg(list, length, start);
	else if (list->args)
		add_in_node_arg(list, length, start);
	return (i);
}

t_tokens *find_files(t_tokens *list)
{
	t_tokens	*tmp;
	int			i;
	int			j;
	char		*filename;

	i = 0;
	tmp = list;
	while (list)
	{
		//while (list->content[i] && list->tokens[i] != EOL)
		while (list->tokens[i] != EOL)
		{
			if (list->tokens[i] >= REDIRECT_IP && list->tokens[i] <= \
			REDIRECT_APPEND)
			{
				while (list->content[i] == '<' || list->content[i] == '>')
					i++;
				while (list->content[i] == ' ')
					i++;
				if (list->content[i])
					i = cut_to_files(list, i, list->tokens[i]);
			}
			else if (list->tokens[i] == RD_TIL_DELIM)
			{
				while (list->content[i] == '<' || list->content[i] == '>')
					i++;
				while (list->content[i] == ' ')
					i++;
				if (list->content[i])
				{
					i = cut_to_files(list, i, list->tokens[i]);
					j = ft_arrlen_c(list->files) - 1;
					filename = heredoc(list->files[j], 1);
					list->files[j] = filename;
				}
			}
			i++;
		}
		i = 0;
		list = list->next;
	}
	return (tmp);
}

int	cut_to_files(t_tokens *list, int i, int val)
{
	int	length;
	int	start;

	length = 0;
	start = i;
	while (list->tokens[i] >= val && !ft_strchr("<>", list->content[i]))
	{
		length++;
		i++;
	}
	if (i > 0)
	{
		length = length - 1;
		i = i - 1;
	}
	if (!list->files)
		transpose_file(list, length, start, val);
	else if (list->files)
	{
		add_in_node_file(list, length, start);
		attach_token(list, start);
	}
	return (i);
}

void	attach_token(t_tokens *list, int place)
{
	int	*tmp;
	int	i;

	i = 0;
	while (list->mini_tok[i] != EOL)
			i++;
	tmp = malloc(sizeof(int) * (i + 2));
	i = 0;
	while (list->mini_tok[i] != EOL)
	{
		tmp[i] = list->mini_tok[i];
		i++;
	}
	tmp[i] = list->tokens[place];
	tmp[i + 1] = EOL;
	free(list->mini_tok);
	list->mini_tok = tmp;
}

void	transpose_file(t_tokens *list, int length, int start, int val)
{	
	int	i;

	i = 0;
	if (list->files)
		free(list->files);
	list->files = malloc(sizeof(char *) * 2);
	list->files[0] = ft_substr(list->content, start, length);
	list->files[1] = NULL;
	if (!list->mini_tok)
	{
		list->mini_tok = malloc(sizeof(int) * 2);
		list->mini_tok[0] = val;
		list->mini_tok[1] = EOL;
	}
	else
		attach_token(list, start);
}

void	transpose_arg(t_tokens *list, int length, int start)
{
	int	i;

	i = 0;
	if (list->args)
	{
		free(list->args);
		list->args = NULL;
	}
	list->args = malloc(sizeof(char *) * 2);
	list->args[0] = ft_substr(list->content, start, (length - 1));
	list->args[1] = 0;
}

void	add_in_node_file(t_tokens *list, int length, int i)
{
	char	**tmp_files;
	int		j;

	j = 0;
	while (list->files[j])
		j++;
	tmp_files = malloc(sizeof(char *) * (j + 2));
	j = 0;
	while (list->files[j])
	{
		tmp_files[j] = ft_strdup(list->files[j]);
		j++;
	}
	tmp_files[j] = malloc(sizeof(char) * (length + 1));
	tmp_files[j] = ft_substr(list->content, i, length);
	tmp_files[j + 1] = NULL;
	j = 0;
	while (tmp_files[j])
		j++;
	j = 0;
	while (list->files[j])
	{
		free (list->files[j]);
		j++;
	}
	list->files = tmp_files;
}

void	add_in_node_arg(t_tokens *list, int length, int i)
{
	char	**tmp_args;
	int		j;

	j = 0;
	while (list->args[j])
		j++;
	tmp_args = malloc(sizeof(char *) * (j + 2));
	j = 0;
	while (list->args[j])
	{
		tmp_args[j] = ft_strdup(list->args[j]);
		j++;
	}
	tmp_args[j] = malloc(length + 1);
	tmp_args[j] = ft_substr(list->content, i, length);
	tmp_args[j + 1] = NULL;
	j = 0;
	while (list->args[j])
	{
		free (list->args[j]);
		j++;
	}
	list->args = tmp_args;
}

void free_arr_null(char ***ptr)
{
	free(**ptr);
	**ptr = 0;
}

void free_str_null(char **ptr)
{
	free(*ptr);
	*ptr = 0;
}
