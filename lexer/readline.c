/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:49:07 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/14 16:39:22 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

static int	hor_pos(void);

static int	is_empty_line(char *line)
{
	if (!line)
		return (EMPTY);
	while (*line)
	{
		if (*line > 32)
			return (FULL);
		line++;
	}
	return (EMPTY);
}

char	*read_the_line(void)
{
	char	*c;
	char	*line;
	int		x;
	char	*s;

	line = NULL;
	rl_outstream = stderr;
	x = hor_pos();
	line = readline("type away; ");
	if (!line)
	{
		c = ft_itoa(x);
		s = ft_strjoin("\e[", c);
		free(c);
		c = ft_strjoin(s, "G\e[1Atype away; exit\n");
		ft_putstr_fd(c, 1);
		exit(g_exit_code);
	}
	if (is_empty_line(line) == FULL)
		add_history(line);
	return (line);
}

static int	get_pos_data(char *ptr)
{
	char	ch;
	int		ret;
	char	buf[30];
	int		i;

	ch = 0;
	i = 0;
	while (ch != 'R')
	{
		ret = read(0, &ch, 1);
		if (!ret)
			return (0);
		buf[i] = ch;
		i++;
	}
	ptr = ft_strchr(buf + 1, ';');
	i = ft_atoi(ptr + 1);
	return (i);
}

static int	hor_pos(void)
{
	char			*ptr;
	int				i;
	struct termios	term;
	struct termios	restore;

	ptr = 0;
	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
	write(1, "\033[6n", 4);
	i = get_pos_data(ptr);
	if (!i)
	{
		tcsetattr(0, TCSANOW, &restore);
		fprintf(stderr, "getpos: error reading response!\n");
		return (0);
	}
	tcsetattr(0, TCSANOW, &restore);
	return (i);
}

// char	*read_the_line_again(char *first_half)
// {
// 	char	*c;
// 	char	*line;
// 	int		x;
// 	char	*s;

// 	line = NULL;
// 	rl_outstream = stderr;
// 	x = hor_pos();
// 	line = readline("> ");
// 	if (!line)
// 	{
// 		c = ft_itoa(x);
// 		s = ft_strjoin("\e[", c);
// 		free(c);
// 		c = ft_strjoin(s, "G\e[1Aminishell; 
// syntax error: unexpected end of file\n");
// 		ft_putstr_fd(c, 1);
// 		free(c);
// 		free(s);
// 		free(first_half);
// 		return (0);
// 	}
// 	s = ft_strjoin(first_half, line);
// 	if (is_empty_line(s) == FULL)
// 		add_history(s);
// 	free(first_half);
// 	free(line);
// 	return (s);
// }