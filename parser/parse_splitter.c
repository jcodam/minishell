/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_splitter.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 18:49:19 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/03/24 19:27:18 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

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

t_tokens	*primary_split(char *input, int *arr, t_tokens *list)
{
	//int	i;

	//i = 0;
	list->content = input;
	list->tokens = arr;
	list = split_on_amps(list);
	//print_all_tokens(list);
	//list = split_on_or(list);
	//list = split_on_pipes(list);
	trim_spaces(list);
	//print_all_tokens(list);
	//list = find_docs(list);
	//ft_putstr_fd("after find docs\n", 1);
	//list = find_flags(list);
	//list = transpose_args(list);
	return (list);
}

void	trim_spaces(t_tokens *list)
{
	int		start;
	int		end;
	char	*tmp;
	int		*arr;

	//start = 0;
	//end = ft_strlen(list->content);
	while (list)
	{
		arr = list->tokens;
		tmp = list->content;
		start = 0;
		end = ((ft_strlen(list->content) - 1));
		//printf("end: %d", end);
		while (list->content[start] == ' ')
			start++;
		while (list->content[end] == ' ')
			end--;
		//printf("list->content (pre): %s\n", tmp);
		//printf("list->tokens (pre): ");
		//print_tokens(arr);
		//printf("\n");
		//printf("start: %d\n", start);
		//printf("end: %d\n", end);
		//printf("content: [%s]\n", list->content);
		list->content = ft_substr(tmp, start, (end - start));
		list->tokens = ft_subarr(list->tokens, start, (end - start));
		//printf("list->tokens (post): ");
		//print_tokens(arr);
		//printf("\n");
		list = list->next;
	}
}

t_tokens	*split_on_amps(t_tokens *list)
{
	t_tokens	*tmp;
	int			place;

	tmp = list;
	place = 0;
	while (place != -1 && list)
	{
		place = find_tokens(SPLIT_AND, list);
		//printf("place; %d", place);
		if (place != -1)
		{
			split_to_node(list, place, 2);
			list->next->log_op = OPP_AND;
		}
		if (place == -1)
			break ;
		//printf("current content: [%s]\n", list->content);
		//if (list->next->content)
		//	printf("next content: [%s]\n", list->next->content);
		if (list->next)
			list = list->next;
	}
	return (tmp);
}

t_tokens	*split_on_or(t_tokens *list)
{
	t_tokens	*tmp;
	int			place;

	tmp = list;
	place = 0;
	while (place != -1 && list)
	{
		while (list->next && find_tokens(SPLIT_OR, list) == -1)
			list = list->next;
		if (list)
			place = find_tokens(SPLIT_OR, list);
		if (place != -1)
		{
			split_to_node(list, place, 2);
			list->next->log_op = OPP_OR;
		}
	}
	return (tmp);
}

t_tokens	*split_on_pipes(t_tokens *list)
{
	t_tokens	*tmp;
	int			place;

	tmp = list;
	place = 0;
	while (place != -1 && list)
	{
		while (list->next && find_tokens(PIPE, list) == -1)
			list = list->next;
		if (list)
			place = find_tokens(PIPE, list);
		if (place != -1)
		{
			split_to_node(list, place, 2);
			list->next->log_op = OPP_PIPE;
		}
	}
	return (tmp);
}

int find_tokens(int val, t_tokens *list)
{
	int	i;

	i = 0;
	while (list->tokens[i] != -2 && list)
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

	length = ft_strlen(node->content);
	new = malloc(sizeof(t_tokens));
	if (node->next)
		new->next = node->next;
	else
		new->next = 0;
	node->next = new;
	fill_node_split(node, split_point, noc, length);
}

void	fill_node_split(t_tokens	*node, int split_point, int noc, int length)
{
	char	*str;
	int		*arr;

	str = node->content;
	arr = node->tokens;
	node->next->content = ft_substr(node->content, (split_point + noc), \
	(length - ((split_point + noc) - 1)));
	node->content = ft_substr(str, 0, (split_point - noc));
	free(str);
	node->next->tokens = ft_subarr(node->tokens, (split_point + noc), \
	(length - ((split_point + noc) - 1)));
	node->tokens = ft_subarr(arr, 0, (split_point - noc));
	free(arr);
}

int	*ft_subarr(int *arr, unsigned int start, size_t len)
{
	unsigned int	i;
	int				*newarr;
	size_t			arrlen;

	i = 0;
	if (!arr)
		return (0);
	arrlen = ar_len(arr);
	if (start > arrlen)
		return (0);
	newarr = (int *)malloc((len + 1) * sizeof(int));
	if (!newarr)
		return (0);
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
	newstr = (char *)malloc((len + 1) * sizeof(char));
	if (newstr == 0)
		return (NULL);
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
	ft_putstr_fd("tokens: [", 1);
	while (arr[i] != -2 && arr[i])
	{
		ft_putnbr_fd((signed int)arr[i], 1);
		i++;
	}
	ft_putnbr_fd((signed int)arr[i], 1);
	ft_putstr_fd("]", 1);
}

int	ar_len(int *arr)
{
	int	len;

	len = 0;
	while (arr[len] != -2 && len < 10)
		len++;
	if (len > 0)
		len--;
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
		while (list->content[i])
		{
			if (list->tokens[i] >= 2 && list->tokens[i] <= 5)
			{
				print_tokens(list->tokens);
				i = cut_to_files(list, i, list->tokens[i]);
			}
			else
				i++;
		}
		list = list->next;
	}
	return (tmp);
}

// make this work
int	cut_to_files(t_tokens *list, int i, int val)
{
	int	length;

	length = 0;
	while (list->tokens[i] == val)
	{
		length++;
		i++;
	}
	if (!list->files)
	{
		list->files = malloc(sizeof(char *) * 2);
		list->files[0] = malloc(sizeof(char) * (length + 1));
		list->files[0] = ft_substr(list->content, i, length);
		list->files[1] = NULL;
		list->args = malloc(sizeof(char *) * 2);
		list->args[0] = malloc(sizeof(char) * 5);
		list->args[0][0] = 't';
		list->args[0][1] = 'e';
		list->args[0][2] = 's';
		list->args[0][3] = 't';
		list->args[0][4] = '\0';
		list->args[1] = NULL;
		list->mini_tok = malloc(sizeof(int *));
		list->mini_tok = &val;
	}
	else if (list->files)
	{
		write(1, "hello\n", 1);
		add_in_node(list, length, i);
	}
	return (i + (length - 1));
}

//function to add 'files' to the files array in the node if one already exists.
void	add_in_node(t_tokens *list, int length, int i)
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
