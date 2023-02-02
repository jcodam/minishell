/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/18 17:28:27 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/02 14:11:40 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	ft_change_dir(char *path)
{
	int	i;

	path += 3;
	i = chdir(path);
	ft_putnbr_fd(i, 1);
	if (i == -1)
		ft_putendl_fd("cd argument is not corect", 1);
}
