/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:00:29 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/20 16:56:20 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	g_exit_code = 0;

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	struct termios		term_struct;
	t_tokens			*splitted;
	t_super				*super;
	t_arglist			*args;
	int 				i;

	i = 0;
	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &term_struct);
	tcgetattr(STDOUT_FILENO, &term_struct);
	tcgetattr(STDERR_FILENO, &term_struct);
	term_struct.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_struct);
	super = malloc(sizeof(t_super));
	args = malloc(sizeof(t_arglist));
	super->env = copy_env(envp);
	super->term_struct = &term_struct;
	while (1)
	{
		set_signal_parrent();
		line = read_the_line();
		// splitted = main_loop(line);
		// print_all_tokens(splitted);
		// block_signal();
		// tcsetattr(STDIN_FILENO, TCSANOW, &term_struct);
		// tcsetattr(STDOUT_FILENO, TCSANOW, &term_struct);
		// tcsetattr(STDERR_FILENO, TCSANOW, &term_struct);
		// exit(0);
		// while (splitted)
		// {
		// 	what_cmd(splitted->content, super);
		// 	splitted = splitted->next;
		// }
		if (line && *line)
			what_cmd(line, super);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_struct);
		tcsetattr(STDOUT_FILENO, TCSAFLUSH, &term_struct);
		tcsetattr(STDERR_FILENO, TCSAFLUSH, &term_struct);
		free(line);
	}
	(void)splitted;
	return (0);
}

/*t_arglist	*convert_list(t_tokens *source)
{
	t_arglist	*dest;

	dest = malloc(sizeof(t_arglist));
	dest->next = 0;
	if (!source)
		return (0);
	while (source->next)
	{
		dest = add_node_args(dest, source);
		source = source->next;
	}
	dest = add_node_args(dest, source);
	return (dest);
}

t_arglist	*add_node_args(t_arglist *args, t_tokens *source)
{
	t_arglist	*node;
	t_arglist	*tmp;

	tmp = args;
	node = malloc(sizeof(node));
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	tmp->next->next = 0;
	tmp->next->arg = &source->content;
	return (tmp);
}
*/