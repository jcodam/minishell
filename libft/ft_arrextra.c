/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arrextra.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:12:56 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/19 15:54:34 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arrlen_c(char **arr)
{
	size_t	count;

	count = 0;
	while (arr && arr[count] != '\0')
		count++;
	return (count);
}

void	ft_arrclear_c(char **arr, size_t len)
{
	size_t	count;

	count = 0;
	while (count < len)
	{
		free(arr[count]);
		count++;
	}
	free(arr);
}

char	**ft_arrdup_c(char **arr, size_t len)
{
	size_t	count;
	char	**dest;

	count = 0;
	dest = malloc((len + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (count < len && arr[count] != '\0')
	{
		dest[count] = ft_strdup(arr[count]);
		if (!dest[count])
		{
			ft_arrclear_c(dest, count);
			return (NULL);
		}
		count++;
	}
	dest[count] = NULL;
	return (dest);
}
