/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:49:07 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/22 20:21:36 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	hor_pos(void);
/* 
char *var = read_the_line()
wil wait for and return the line
*/

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}

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
	ft_putstr_fd("\e[s", 2);
	x = hor_pos();
	line = readline("type away; ");
	if (!line)
	{
		c = ft_itoa(x);
		s = ft_strjoin("\e[", c);
		free(c);
		c = ft_strjoin(s, "G\e[1Atype away; exit\n");
		ft_putstr_fd(c, 2);
		exit(0);
	}
	if (is_empty_line(line) == FULL)
		add_history(line);
	return (line);
}

int	get_pos_data(char *ptr)
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

int	hor_pos(void)
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
