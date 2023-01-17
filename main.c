/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:00:29 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/17 16:46:43 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	is_exit(char *line)
{
	char	*s;
	int		i;

	i = 0;
	s = "exit";
	while (s[i] && s[i] == line[i])
		i++;
	if (i == 4)
		exit(0);
}

printf("hello");


int	main(void)
{
	char				*line;
	struct termios		term_struct;

	tcgetattr(STDIN_FILENO, &term_struct);
	tcgetattr(STDOUT_FILENO, &term_struct);
	tcgetattr(STDERR_FILENO, &term_struct);
	term_struct.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_struct);
	while (1)
	{
		set_signal_parrent();
		line = read_the_line();
		is_exit(line);
		block_signal();
		system(line);
		free(line);
	}
	return (0);
}
