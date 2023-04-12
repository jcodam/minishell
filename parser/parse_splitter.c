/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_splitter.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 18:49:19 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/04/11 16:35:09 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		count;

	copy = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	count = 0;
	while (s[count] != '\0')
	{
		copy[count] = s[count];
		count++;
	}
	copy[count] = '\0';
	return (copy);
}

void	ft_putnbr_fd(int n, int fd)
{
	char			c;
	unsigned int	d;

	d = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		d = n * -1;
	}
	c = d % 10 + '0';
	d = d / 10;
	if (d > 0)
		ft_putnbr_fd(d, fd);
	write(fd, &c, 1);
}

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

int find_tokens(int val, t_tokens *list)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(list->content);
	if (!list->tokens)
		return (-1);
	while (list->tokens[i] != -2 && list->content[i])
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
	int			length;
	t_tokens	*new;
	int			*arr;

	arr = NULL;
	length = ft_strlen(node->content);
	new = malloc(sizeof(t_tokens));
	new->tokens = arr;
	new->args = 0;
	new->files = 0;
	new->mini_tok = 0;
	if (node->next)
		new->next = node->next;
	else
		new->next = 0;
	node->next = new;
	fill_node_split(node, split_point, noc, length);
}

void	fill_node_split(t_tokens *node, int split_point, int noc, int length)
{
	char		*str;
	int			*arr;
	size_t		node_2_len;
	size_t		len;

	len = (ft_strlen(node->content) + 1);
	node_2_len = (length) - (split_point + noc);
	//printf("node 2 len: %zu", node_2_len);
	// arr = malloc(sizeof(int) * split_point);
	// str = malloc(node_2_len);
	// str = ft_strdup(node->content);
	// arr = ms_arrdup(node->tokens, len);
	// free(node->content);
	// free(node->tokens);
	arr = node->tokens;
	str = node->content;
	node->next->content = ft_substr(str, (split_point + noc), \
	node_2_len);
	node->content = ft_substr(str, 0, (split_point - 1));
	free(str);
	node->next->tokens = ft_subarr(arr, (split_point + noc), \
	node_2_len);
	node->tokens = ft_subarr(arr, 0, (split_point - 1));
	free(arr);
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
	ret = malloc(len * sizeof(type));
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
	newstr = (char *)malloc((len + 2) * sizeof(char));
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

t_tokens *find_docs(t_tokens *list)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = list;
	while (list)
	{
		while (list->content[i]  && list->tokens[i] != -2)
		{
			if (list->tokens[i] > 1 && list->tokens[i] < 6)
			{
				while (list->content[i] == '<' || list->content[i] == '>')
					i++;
				while (list->content[i] == ' ')
					i++;
				if (list->content[i])
					i = cut_to_files(list, i, list->tokens[i]);
			}
			i++;
		}
		i = 0;
		list = list->next;
	}
	return (tmp);
}

t_tokens *find_args(t_tokens *list)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = list;
	while (list)
	{
		while (list->content[i])
		{
			if (list->tokens[i] == 1 || list->tokens[i] == 0 || \
			list->tokens[i] > 5)
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

	length = 0;
	start = i;
	while (list->tokens[i++] == val)
		length++;
	if (length > 0)
		length = (length - 1);
	if (!list->args)
		transpose_arg(list, length, start, val);
	else if (list->args)
		add_in_node_arg(list, length, i);
	return (i);
}

int	cut_to_files(t_tokens *list, int i, int val)
{
	int	length;
	int	start;

	length = 0;
	start = i;
	while (list->tokens[i] == val)
	{
		length++;
		i++;
	}
	if (length > 0)
	{
		length = (length - 1);
		i--;
	}
	if (!list->files)
		transpose_file(list, length, start, val);
	else if (list->files)
	{
		printf("files exitsts!\n");
		add_in_node_file(list, length, i);
	}
	// printf("i: %d\n", i);
	// printf("length: %d\n", length);
	// printf("start: %d\n", start);
	// printf("val: %d\n", val);
	return (i);
}

void	transpose_file(t_tokens *list, int length, int start, int val)
{	
	int	i;
	int	*tmp;

	i = 0;
	// if (list->files)
	// 	free(list->files);
	list->files = malloc(sizeof(char *) * 2);
	list->files[0] = ft_substr(list->content, start, length);
	list->files[1] = NULL;
	if (!list->mini_tok)
	{
		list->mini_tok = malloc(sizeof(int) * 2);
		list->mini_tok[0] = val;
		list->mini_tok[1] = -2;
	}
	else
	{
		while (list->mini_tok[i] != -2)
			i++;
		tmp = malloc(sizeof(int) * (i + 2));
		i = 0;
		while (list->mini_tok[i] != -2)
		{
			tmp[i] = list->mini_tok[i];
			i++;
		}
		tmp[i] = -2;
		free(list->mini_tok);
		list->mini_tok = tmp;
	}
}

void	transpose_arg(t_tokens *list, int length, int start, int val)
{
	int	i;
	int	*tmp;

	i = 0;
	if (list->args)
		free(list->args);
	list->args = malloc(sizeof(char *) * 2);
	list->args[0] = ft_substr(list->content, start, (length + 1));
	list->args[1] = 0;
	if (!list->mini_tok)
	{
		list->mini_tok = malloc(sizeof(int) * 2);
		list->mini_tok[0] = val;
		list->mini_tok[1] = -2;
	}
	else
	{
		while (list->mini_tok[i] != -2)
			i++;
		tmp = malloc(sizeof(int) * (i + 2));
		i = 0;
		while (list->mini_tok[i] != -2)
		{
			tmp[i] = list->mini_tok[i];
			i++;
		}
		tmp[i] = -2;
		free(list->mini_tok);
		list->mini_tok = tmp;
	}
}

void	add_in_node_file(t_tokens *list, int length, int i)
{
	char	**tmp_files;
	int		j;

	j = 0;
	while (list->files[j])
		j++;
	tmp_files = malloc(sizeof(char *) * (j + 1));
	j = 0;
	while (list->files[j])
	{
		tmp_files[j] = list->files[j];
		j++;
	}
	tmp_files[j] = ft_substr(list->content, i, length);
	tmp_files[j + 1] = NULL;
	j = 0;
	while (list->files[j])
	{
		free (list->files[j]);
		j++;
	}
	free (list->files);
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
		ft_strlcpy(tmp_args[j], list->args[j], ft_strlen(list->args[j]));
		j++;
	}
	tmp_args[j] = ft_substr(list->content, i, length);
	tmp_args[j + 1] = 0;
	j = 0;
	while (list->args[j])
	{
		free (list->args[j]);
		j++;
	}
	free (list->files);
	list->args = tmp_args;
}

// int main(void)
// {
// 	t_tokens	*test;
// 	char		*str;
// 	int			*arr;
// 	int			i;
// 	int			val;

// 	i = 0;
// 	arr = malloc(sizeof(int) * 40);
// 	while (i < 29)
// 		arr[i++] = 3;
// 	arr[5] = 12;
// 	arr[6] = 12;
// 	arr[9] = 7;
// 	arr[12] = 12;
// 	arr[11] = 12;
// 	arr[i] = -2;
// 	//printf("array len: %d", ar_len(arr));
// 	test = malloc (sizeof(t_tokens));
// 	str = ft_strdup("hello world how are you doing");
// 	test = primary_split(str, arr, test);
// 	print_all_tokens(test);
// 	//system("leaks a.out");
//}

// if (line && *line)
// 			what_cmd(list->content, super);
// while (g_exit_code != 0 && list)
// if (line && *line)
// 			what_cmd(line, super);

// while (list)

// *****l
// ****l
// ***l
// **l
