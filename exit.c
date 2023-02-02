/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 13:18:11 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/02 14:36:19 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int	check_arg(char *arg, int exit_code)
{
	while (ft_iswhite_space(*arg))
		arg++;
	if (!*arg)
		exit(exit_code);
	while (ft_isdigit(*arg))
		arg++;
	while (ft_iswhite_space(*arg))
		arg++;
	if (*arg)
		return (1);
	return (0);
}

void	ft_exit_builtin(char *arg, int exit_code)
{
	if (!arg || !*arg)
		exit(exit_code);
	ft_putnbr_fd(ft_atoi(arg), 1);
	write(1, "\nexit\n", 6);
	if (check_arg(arg, exit_code))
	{
		ft_putstr_fd("minishel: exit: ", 1);
		ft_putstr_fd(arg, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(255);
	}
	exit(ft_atoi(arg));
}
