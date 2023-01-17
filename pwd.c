/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:12:12 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/16 17:42:49 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE
#include "all.h"
#include "libft/libft.h"

void	pwd(int output_fd)
{
	char	*cwd;
	int		len;
	cwd = ft_calloc(100, 1);
	getcwd(cwd, 100);
	len = ft_strlen(cwd);
	write(output_fd, cwd, len);
	write(output_fd, "\n", 1);
}

int	main(void)
{
	pwd(1);
	return 0;
}
