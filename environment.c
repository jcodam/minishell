/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 17:05:02 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/26 14:31:42 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	**copy_env(char **env)
{
	int		len;
	char	**dest;

	len = ft_arrlen_c(env);
	dest = ft_arrdup_c(env, len);
	if (!dest)
		exit(0);
	return (dest);
}
