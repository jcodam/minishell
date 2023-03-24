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
	list->content = input;
	list->tokens = arr;
	list->iter = 0;
	list = split_on_amps(list);
	//list = split_on_or(list);
	//list = split_on_pipes(list);
	trim_spaces(list);
	//list = transpose_args(list);
	return (list);
}

void	trim_spaces(t_tokens *list)
{
	int		start;
	int		end;
	char	*tmp;

	start = 0;
	end = ft_strlen(list->content);
	while (list)
	{
		tmp = list->content;
		//printf("node number: %d\n", list->iter);
		//printf("content: [%s]\n", tmp);
		start = 0;
		end = (ft_strlen(list->content) - 1);
		while (tmp[start] == ' ')
			start++;
		while (tmp[end] == ' ')
			end--;
		list->content = ft_substr(tmp, start, ((end - start) + 1));
		list->tokens = ft_subarr(list->tokens, start, ((end - start) + 1));
		list = list->next;
	}
}

t_tokens	*split_on_amps(t_tokens *list)
{
	int			len;
	int			i;
	t_tokens	*tmp;

	tmp = list;
	i = 0;
	len = ft_strlen(list->content);
	while (list)
	{
		// issue somewhere with the tokens.
		while ((find_tokens(12, list) != -1) && list)
		{
			split_to_node(list, find_tokens(12, list), 2, list->iter);
			//printf("find tokens: %d", find_tokens(12, list));
			//print_all_tokens(list);
		}
		list = list->next;
	}
	return (tmp);
}

t_tokens	*split_on_or(t_tokens *list)
{
	int			len;
	int			i;
	t_tokens	*tmp;

	tmp = list;
	i = 0;
	len = ft_strlen(list->content);
	while (list)
	{
		while (find_tokens(11, list) != -1)
		{
			split_to_node(list, find_tokens(11, list), 2, list->iter);
			print_all_tokens(list);
		}
		list = list->next;
	}
	return (tmp);
}

t_tokens	*split_on_pipes(t_tokens *list)
{
	int			len;
	int			i;
	t_tokens	*tmp;

	tmp = list;
	i = 0;
	len = ft_strlen(list->content);
	while (list)
	{
		while (find_tokens(7, list) != -1)
			split_to_node(list, find_tokens(7, list), 1, list->iter);
		list = list->next;
	}
	return (tmp);
}

int find_tokens(int val, t_tokens *list)
{
	int	i;

	i = 0;
	while (list->tokens[i] != -2)
	{
		if (list->tokens[i] == val)
			return (i + 1);
		//printf("array val: %d\n", list->tokens[i]);
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
void	split_to_node(t_tokens *node, int split_point, int noc, int node_nr)
{
	int			length;
	t_tokens	*new;

	while (node_nr)
	{
		node = node->next;
		node_nr--;
	}
	noc -= 1;
	length = ft_strlen(node->content);
	new = malloc(sizeof(t_tokens));
	if (node->next)
		new->next = node->next;
	node->next = new;
	fill_node_split(node, split_point, noc, length);
	while (new)
	{
		new->iter++;
		new = new->next;
	}
}

void	fill_node_split(t_tokens	*node, int split_point, int noc, int length)
{
	char	*str;
	int		*arr;

	str = node->content;
	arr = node->tokens;
	node->next->content = ft_substr(node->content, (split_point + noc), \
	(length - (split_point + noc)));
	node->content = ft_substr(str, 0, (split_point - 1));
	free(str);
	node->next->tokens = ft_subarr(node->tokens, (split_point + noc), \
	(length - (split_point + noc)));
	node->tokens = ft_subarr(arr, 0, (split_point - 1));
	free(arr);
}

int	*ft_subarr(int *arr, unsigned int start, size_t len)
{
	unsigned int	i;
	int				*newarr;
	size_t			arrlen;

	i = 0;
	if (arr == 0)
		return (0);
	arrlen = ar_len(arr);
	if (start > arrlen)
		return (0);
	newarr = (int *)malloc((len + 1) * sizeof(int));
	if (!newarr)
		return (0);
	while (i < len)
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
	while (i < len)
	{
		newstr[i] = s[start + i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

void print_tokens(int *arr)
{
	int	i;

	i = 0;
	ft_putstr_fd("tokens: ", 1);
	while (arr[i] != -2)
	{
		ft_putnbr_fd(arr[i], 1);
		i++;
	}
}

int	ar_len(int *arr)
{
	size_t	len;

	len = 0;
	while (arr[len] != -2)
		len++;
	return (len);
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
