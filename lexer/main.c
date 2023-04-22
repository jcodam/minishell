/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:00:29 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/22 16:15:16 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"
#include "../headers/quotedef.h"

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

/*static int	nb_of_non_quotes(char *str)
{
	int	index;
	int	quote_mark;
	int	nb_non_quotes;

	nb_non_quotes = 0;
	quote_mark = NO_QUOTE;
	index = 0;
	while (str[index])
	{
		if (str[index] == '"' && quote_mark == NO_QUOTE)
			quote_mark = DOUBLE_QUOTE;
		else if (str[index] == '"' && quote_mark == DOUBLE_QUOTE)
			quote_mark = NO_QUOTE;
		else if (str[index] == '\'' && quote_mark == NO_QUOTE)
			quote_mark = SINGLE_QUOTE;
		else if (str[index] == '\'' && quote_mark == SINGLE_QUOTE)
			quote_mark = NO_QUOTE;
		index++;
	}
	return (quote_mark);
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
		while (nb_of_non_quotes(line) > NO_QUOTE)
			line = read_the_line_again(line);
		if (line)
		{
			ft_putendl_fd(line,1);
		// splitted = main_loop(line);
		// if (splitted)
		// 	what_cmd(splitted, super);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, super->term_struct);
		tcsetattr(STDOUT_FILENO, TCSAFLUSH, super->term_struct);
		tcsetattr(STDERR_FILENO, TCSAFLUSH, super->term_struct);
		// free_list(splitted);
		free(line);
		}
	}
	(void)splitted;
	return (0);
}*/
		// print_all_tokens(splitted);

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

void	del_files(char **files, int *tokens)
{
	int	index;
	int	error;

	error = 0;
	index = 0;
	while (files && files[index])
	{
		if (tokens[index] == RD_TIL_DELIM)
			error = unlink(files[index]);
		if (error == -1)
			perror(files[index]);
		index++;
	}
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
		del_files(list->files, list->mini_tok);
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
