/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:12:12 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/14 18:19:58 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#define _POSIX_SOURCE

void	ft_pwd(t_super *super, int output_fd)
{
	char	*cwd;
	int		len;

	super->exit_code = 0;
	cwd = ft_calloc(100, 1);
	if (!getcwd(cwd, 100))
		super->exit_code = 1;
	len = ft_strlen(cwd);
	write(output_fd, cwd, len);
	write(output_fd, "\n", 1);
	free(cwd);
}
