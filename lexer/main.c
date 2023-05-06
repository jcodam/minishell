/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:00:29 by jbax          #+#    #+#                 */
/*   Updated: 2023/05/05 20:16:55 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"
#include "../headers/quotedef.h"
//#include <crtdbg.h>

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

static int	set_shlvl(t_super *super, int nbr)
{
	char	**exprt;
	char	*temp;
	char	*temp1;

	exprt = 0;
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
	shell_level(super);
	while (1)
	{
		set_signal_parrent();
		line = read_the_line();
		block_signal();
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
