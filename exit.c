/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 13:18:11 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/09 13:37:10 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

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

void	ft_exit_builtin(char **arg, t_super *super)
{
	ft_putstr_fd("exit\n", 1);
	if (!arg || !*(&arg[1]))
		exit(super->exit_code);
	if (check_arg(arg[1], super->exit_code))
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
		super->exit_code = 1;
	}
	else
		exit(ft_atoi(arg[1]) % 256);
}
