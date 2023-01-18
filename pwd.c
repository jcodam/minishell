/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:12:12 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/18 17:47:22 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#define _POSIX_SOURCE

void	ft_pwd(int output_fd)
{
	char	*cwd;
	int		len;

	cwd = ft_calloc(100, 1);
	getcwd(cwd, 100);
	len = ft_strlen(cwd);
	write(output_fd, cwd, len);
	write(output_fd, "\n", 1);
	free(cwd);
}
