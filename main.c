/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:00:29 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/22 21:34:25 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	struct termios		term_struct;
	t_tokens			*splitted;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &term_struct);
	tcgetattr(STDOUT_FILENO, &term_struct);
	tcgetattr(STDERR_FILENO, &term_struct);
	term_struct.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_struct);
	while (1)
	{
		set_signal_parrent();
		line = read_the_line();
		splitted = tokanize(line);
		print_all_tokens(splitted);
		block_signal();
		what_cmd(line, envp);
		// system(line);
		free(line);
	}
	return (0);
}

int	print_all_tokens(t_tokens *list)
{
	t_tokens	*tmp;

	tmp = list;
	if (!list)
		return (0);
	while (tmp->next)
	{
		write(1, tmp->content, sizeof(tmp->content));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	if (tmp->content)
		write(1, tmp->content, sizeof(tmp->content));
	return (1);
}
