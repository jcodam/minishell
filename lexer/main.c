/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:00:29 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/12 15:13:23 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

int	g_exit_code = 0;

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	struct termios		term_struct;
	t_tokens			*splitted;
	t_super				*super;
	t_arglist			*args;

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
		splitted = main_loop(line);
		print_all_tokens(splitted);
		// tcsetattr(STDIN_FILENO, TCSANOW, &term_struct);
		// tcsetattr(STDOUT_FILENO, TCSANOW, &term_struct);
		// tcsetattr(STDERR_FILENO, TCSANOW, &term_struct);
		// while (splitted)
		// {
		// 	what_cmd(splitted->content, super);
		// 	splitted = splitted->next;
		// }
		// if (line && *line)
		// 	what_cmd(line, super);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_struct);
		tcsetattr(STDOUT_FILENO, TCSAFLUSH, &term_struct);
		tcsetattr(STDERR_FILENO, TCSAFLUSH, &term_struct);
		// free_list(splitted);
		//system("leaks minishell");
	}
	(void)splitted;
	return (0);
}

void	free_list(t_tokens *list)
{
	t_tokens	*tmp;
	int			i;

	while (list)
	{
		i = 0;
		tmp = list->next;
		if (list->content)
			free(list->content);
		if (list->tokens)
			free(list->tokens);
		if (list->args)
		{
			while (list->args[i])
				free(list->args[i++]);
			free(list->args);
		}
		i = 0;
		if (list->files)
		{
			while (list->files[i])
				free(list->files[i++]);
			free(list->files);
		}
		if (list->mini_tok)
			free(list->mini_tok);
		free(list);
		list = tmp;
	}
}
