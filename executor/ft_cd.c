/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/18 17:28:27 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/21 19:34:31 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

void	ft_change_dir(char *path)
{
	int	i;

	if (!path)
		path = "";
	i = chdir(path);
	if (i == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd(":No such file or directory\n", 1);
		g_exit_code = 1;
	}
}
