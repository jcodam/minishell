/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:00:29 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/14 15:11:49 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

int	g_exit_code = 0;

void	prep_terms(t_super *super, char **envp, struct termios *term_struct)
{
	tcgetattr(STDIN_FILENO, term_struct);
	tcgetattr(STDOUT_FILENO, term_struct);
	tcgetattr(STDERR_FILENO, term_struct);
	(*term_struct).c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, term_struct);
	super->env = copy_env(envp);
	super->term_struct = term_struct;
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	t_tokens			*splitted;
	t_super				*super;
	struct termios		term_struct;

	(void)argc;
	(void)argv;
	super = malloc(sizeof(t_super));
	prep_terms(super, envp, &term_struct);
	while (1)
	{
		set_signal_parrent();
		line = read_the_line();
		splitted = main_loop(line);
		print_all_tokens(splitted);
		if (splitted)
			what_cmd(splitted, super);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, super->term_struct);
		tcsetattr(STDOUT_FILENO, TCSAFLUSH, super->term_struct);
		tcsetattr(STDERR_FILENO, TCSAFLUSH, super->term_struct);
		free_list(splitted);
	}
	(void)splitted;
	return (0);
}


void	free_list(t_tokens *list)
{
	t_tokens	*tmp;

	while (list)
	{
		tmp = list->next;
		if (list->content)
			free(list->content);
		if (list->tokens)
			free(list->tokens);
		if (list->args)
		{
			ft_arrclear_c(list->args, ft_arrlen_c(list->args));
		}
		if (list->files)
		{
			ft_arrclear_c(list->files, ft_arrlen_c(list->files));
		}
		if (list->mini_tok)
			free(list->mini_tok);
		free(list);
		list = tmp;
	}
}
