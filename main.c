/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:00:29 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/24 19:15:59 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	**test(char **arr)
{
	int i;
	ft_putstr_fd("\n\n", 1);
	ft_putarrs_fd(arr, 1);
	arr = ft_arradd_index(arr, "dodo=poopyhead", 0);
	arr = ft_arradd_index(arr, "blabla=poopyhead", 5);
	arr = ft_arradd_index(arr, "abc=poopyhead", 23);
	ft_putstr_fd("\n\n", 1);
	ft_putarrs_fd(arr, 1);
	arr = ft_arrdell_index(arr, 5);
	ft_putstr_fd("\n\n", 1);
	ft_putarrs_fd(arr, 1);
	ft_putstr_fd("\n\n", 1);
	ft_putendl_fd(ft_arrnstr(arr, "blalba=", &i), 1);
	ft_putstr_fd("\n\n", 1);
	ft_putendl_fd(ft_arrnstr(arr, "abc=", &i), 1);
	arr = ft_arrdell_index(arr, i);
	ft_putstr_fd("\n\n", 1);
	ft_putarrs_fd(arr, 1);
	return (arr);
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	struct termios		term_struct;
	char				**env;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &term_struct);
	tcgetattr(STDOUT_FILENO, &term_struct);
	tcgetattr(STDERR_FILENO, &term_struct);
	term_struct.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_struct);
	env = copy_env(envp);
	ft_arrclear_c(env, ft_arrlen_c(env));
	env = copy_env(envp);
	env = test(env);
	while (1)
	{
		set_signal_parrent();
		line = read_the_line();
		// block_signal();
		what_cmd(line, env);
		// system(line);
		free(line);
	}
	return (0);
}
