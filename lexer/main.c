/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:00:29 by jbax          #+#    #+#                 */
/*   Updated: 2023/05/12 16:22:20 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"
#include "../headers/quotedef.h"

int	g_exit_code = 0;

t_super	*prep_terms(char **envp, struct termios *term_struct)
{
	t_super	*super;

	super = malloc(sizeof(t_super));
	if (!super)
		exit_errbug("start up, malloc failed", "");
	super->restore_term = malloc(sizeof(struct termios));
	if (!super->restore_term)
		exit_errbug("start up, malloc failed", "");
	tcgetattr(STDIN_FILENO, super->restore_term);
	tcgetattr(STDOUT_FILENO, super->restore_term);
	tcgetattr(STDERR_FILENO, super->restore_term);
	tcgetattr(STDIN_FILENO, term_struct);
	tcgetattr(STDOUT_FILENO, term_struct);
	tcgetattr(STDERR_FILENO, term_struct);
	(*term_struct).c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, term_struct);
	super->env = copy_env(envp);
	super->term_struct = term_struct;
	return (super);
}

static int	set_shlvl(t_super *super, int nbr)
{
	char	**exprt;
	char	*temp;
	char	*temp1;
	int		dash;

	exprt = 0;
	dash = ft_env_index(super->env, "_");
	if (dash >= 0)
		super->env = ft_arrdell_index(super->env, dash, free);
	temp = ft_itoa(nbr);
	temp1 = ft_strjoin("SHLVL=", temp);
	free(temp);
	temp = ft_strdup("export");
	exprt = ft_arradd_index(exprt, temp, 0);
	exprt = ft_arradd_index(exprt, temp1, 1);
	ft_export(super, exprt, 1);
	ft_arrclear_c(exprt, ft_arrlen_c(exprt));
	return (0);
}

static int	shell_level(t_super *super)
{
	char	*shelllvl;
	int		shel;

	shelllvl = ft_arrnstr(super->env, "SHLVL=", &shel);
	if (!shelllvl)
		shel = 1;
	else
		shel = ft_atoi(shelllvl + 6);
	if (shel == 2147483647)
		shel = -1;
	shel++;
	if (shel < 0)
		shel = 0;
	else if (shel == 2147483647)
	{
		ft_putstr_fd("minishell: warning: shell level (2147483647)", 2);
		ft_putstr_fd(" too high, resetting to 1\n", 2);
		shel = 1;
	}
	set_shlvl(super, shel);
	return (0);
}

static void	options_pipes(int argc, char **argv, t_super *super)
{
	char		*line;
	t_tokens	*splitted;
	int			options;

	shell_level(super);
	options = 0;
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 2))
		options = 1;
	set_signal_parrent('p');
	set_term(super->term_struct, TCSAFLUSH);
	if (options)
		line = ft_strdup(argv[2]);
	else
		line = first_read_line();
	set_term(super->restore_term, TCSANOW);
	if (!line)
		exit(g_exit_code);
	block_signal();
	splitted = main_loop(line, super);
	if (splitted)
		what_cmd(splitted, super);
	free_list(splitted);
	if (options)
		exit(g_exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	t_tokens			*splitted;
	t_super				*super;
	struct termios		term_struct;

	super = prep_terms(envp, &term_struct);
	options_pipes(argc, argv, super);
	while (1)
	{
		set_signal_parrent('p');
		set_term(super->term_struct, TCSAFLUSH);
		if (isatty(STDIN_FILENO))
			line = read_the_line();
		else
			line = first_read_line();
		set_term(super->restore_term, TCSANOW);
		if (!line)
			exit(g_exit_code);
		block_signal();
		splitted = main_loop(line, super);
		if (splitted)
			what_cmd(splitted, super);
		free_list(splitted);
	}
	return (0);
}
