/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:49:07 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/11 15:02:34 by jbax          ########   odam.nl         */
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

	line = NULL;
	while (!line)
		line = readline(0);
	if (is_empty_line(line) == FULL)
			add_history(line);
	return (line);
}
