/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/18 17:28:27 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/22 18:36:32 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

void	ft_change_dir(char *path)
{
	int	i;

	i = chdir(path);
	ft_putnbr_fd(i, 1);
	if (i == -1)
		ft_putendl_fd("cd argument is not corect", 1);
}
