/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:00:29 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/11 15:02:43 by jbax          ########   odam.nl         */
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

int	main(void)
{
	char				*line;
	static int			i = 0;
	struct termios		term_struct;

	tcgetattr(STDIN_FILENO, &term_struct);
	tcgetattr(STDOUT_FILENO, &term_struct);
	tcgetattr(STDERR_FILENO, &term_struct);
	term_struct.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_struct);
	set_signal_parrent();
	while (1)
	{
		printf("type your comment bellow;%d\n", i);
		line = read_the_line();
		is_exit(line);
		system(line);
		free(line);
	}
	return (0);
}
