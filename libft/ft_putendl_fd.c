/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 17:54:37 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/24 19:13:16 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		while (*s != '\0')
		{
			write(fd, s, 1);
			s++;
		}
		write(fd, "\n", 1);
	}
}
