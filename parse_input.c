/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:35:35 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/02/20 16:21:22 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_tokens	*main_loop(char *input)
{
	int			len;
	int			*arr;
	t_tokens	*list;

	list = malloc(sizeof(t_tokens));
	list->content = 0;
	list->next = 0;
	list->iter = 0;
	len = ft_strlen(input);
	arr = make_arr(len);
	arr = tokanize(input, arr);
	list = split_into_list(input, arr, list);
	print_array(arr);
	//print_all_tokens(list);
	return (list);
}

int	*tokanize(char *input, int *arr)
{
	arr = label_quotes(input, arr, 1);
	arr = label_quotes(input, arr, 0);
	arr = check_operators(input, arr);
	arr = command_after_pipe(input, arr);
	arr = trim_spaces(input, arr);
	arr = check_commands(input, arr);
	return (arr);
}

t_tokens	*split_into_list(char *input, int *arr, t_tokens *top)
{
	static int	start = 0;
	//static int	iteration = 0;
	int			max;
	int			end;

	end = 0;
	max = ft_strlen(input);
	while (start < max)
	{
		end = (start + get_node_length(arr, start));
		if (start == 0)
			fill_node(top, input, start, end);
		else
			top = get_node(start, arr, input, top);
		if (start == end)
			start++;
		else
			start = end;
	}
	return (top);
}

t_tokens	*get_node(int start, int *arr, char *input, t_tokens *top)
{
	int			end;
	char		*str;
	int			i;
	t_tokens	*tmp;

	i = 0;
	end = start;
	while (arr[end] == arr[start])
		end++;
	if (arr[start] != 8)
	{
		tmp = setup_new_node(top);
		str = ms_calloc(0, ((end - start) + 1));
		while (start < end)
		{
			str[i] = input[start];
			i++;
			start++;
		}
		str[i] = '\0';
		tmp->content = str;
		tmp->next = 0;
	}
	return (top);
}

int	*label_vals(int start, int end, int *arr, int sig)
{
	if (end != start)
	{
		while (start <= end)
		{
			arr[start] = sig;
			start++;
		}
	}
	return (arr);
}

// void	fill_node(t_tokens *node, char *input, int start, int end)
// {
// 	char	*string;
// 	int		i;

// 	i = 0;
// 	string = malloc((end - start) + 1);
// 	while (start < end)
// 	{
// 		string[i] = input[start];
// 		i++;
// 		start++;
// 	}
// 	string[i] = '\0';
// 	node->content = string;
// 	node->iter = 0;
// }

// int	main(void)
// {
// 	main_loop("ls -la 'ls -la' | cat -la > 'outfile'");
// }

// void	ft_putnbr_fd(int n, int fd)
// {
// 	char			c;
// 	unsigned int	d;

// 	d = n;
// 	if (n < 0)
// 	{
// 		write(fd, "-", 1);
// 		d = n * -1;
// 	}
// 	c = d % 10 + '0';
// 	d = d / 10;
// 	if (d > 0)
// 		ft_putnbr_fd(d, fd);
// 	write(fd, &c, 1);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	count;

// 	count = 0;
// 	while (*s != '\0')
// 	{
// 		count++;
// 		s++;
// 	}
// 	return (count);
// }

// void	ft_putstr_fd(char *s, int fd)
// {
// 	while (*s != '\0')
// 	{
// 		write(fd, s, 1);
// 		s++;
// 	}
// }

// t_tokens	*new_node(char *input, int type, int i)
// {
// 	t_tokens	*new;

// 	new = (t_tokens *)malloc(sizeof(t_tokens));
// 	new->type = type;
// 	new->content = input;
// 	new->next = 0;
// 	new->iter = i;
// 	return (new);
// }