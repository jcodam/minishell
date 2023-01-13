/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:49:07 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/13 17:24:47 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
/* 
char *var = read_the_line()
wil wait for and return the line
*/

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
	char	*line;
	static char	*promt = NULL;

	if (!promt)
		promt = ttyname(0);
	line = NULL;
	line = readline("type away; ");
	if (!line)
	{
		rl_replace_line("exit\n", 0);
		rl_on_new_line();
		rl_redisplay();
		// write(1, "exit\n", 5);
		exit(0);
	}
	if (is_empty_line(line) == FULL)
			add_history(line);
	return (line);
}
