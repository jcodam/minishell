/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:49:07 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/17 16:53:07 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

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
	char		*line;

	line = NULL;
	rl_outstream = stderr;
	line = readline("type away; ");
	if (!line)
	{
		ft_putstr_fd("\e[1Atype away; exit\n", 2);
		exit(0);
	}
	if (is_empty_line(line) == FULL)
		add_history(line);
	return (line);
}
