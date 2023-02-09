/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:00:29 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/09 14:42:51 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	struct termios		term_struct;
	t_tokens			*splitted;
	t_super				*super;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &term_struct);
	tcgetattr(STDOUT_FILENO, &term_struct);
	tcgetattr(STDERR_FILENO, &term_struct);
	term_struct.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_struct);
	super = malloc(sizeof(t_super));
	super->env = copy_env(envp);
	super->exit_code = 0;
	while (1)
	{
		set_signal_parrent();
		line = read_the_line();
		// splitted = tokanize(line);
		// print_all_tokens(splitted);
		// block_signal();
		what_cmd(line, super);
		// system(line);
		free(line);
	}
	(void)splitted;
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
