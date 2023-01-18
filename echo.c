/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/23 17:22:51 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/18 19:05:03 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	ft_echo(char *str, int argument, int output_fd)
{
	str += 5;
	if (argument)
	{
		str += 2;
		ft_putstr_fd(str, output_fd);
	}
	else
		ft_putendl_fd(str, output_fd);
}
