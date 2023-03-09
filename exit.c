/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 13:18:11 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/02 16:48:45 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	exit_errbug(char *error, char *debug)
{
	printf("%s\n%s\n", error, debug);
	exit(g_exit_code);
}

static int	check_arg(char *arg, int exit_code)
{
	(void)exit_code;
	if (*arg == '+' || *arg == '-')
		arg++;
	while (ft_isdigit(*arg))
		arg++;
	if (*arg)
		return (1);
	return (0);
}

void	ft_exit_builtin(char **arg)
{
	ft_putstr_fd("exit\n", 1);
	if (!arg || !*(&arg[1]))
		exit(g_exit_code);
	if (check_arg(arg[1], g_exit_code))
	{
		if (!arg[2])
		{
			ft_putstr_fd("minishel: exit: ", 1);
			ft_putstr_fd(arg[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			exit(255);
		}
	}
	if (arg[2])
	{
		ft_putstr_fd("minishel: exit: too many arguments\n", 1);
		g_exit_code = 1;
	}
	else
		exit(ft_atoi(arg[1]) % 256);
}
