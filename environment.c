/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 17:05:02 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/24 19:07:52 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/* del string 
add string 
search string
*/
char	**ft_arrdell_index(char **arr, int index)
{
	char	**dest;
	int		count;
	int		ofset;

	ofset = 0;
	count = 0;
	dest = malloc(ft_arrlen_c(arr) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (arr[count])
	{
		if (count != index)
			dest[count + ofset] = arr[count];
		else
			ofset = -1;
		count++;
	}
	dest[count + ofset] = NULL;
	free(arr);
	return (dest);
}

char	**ft_arradd_index(char **arr, char *s, int index)
{
	char	**dest;
	int		count;
	int		ofset;

	count = 0;
	ofset = 0;
	dest = malloc((ft_arrlen_c(arr) + 2) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (arr[count])
	{
		if (count == index)
		{
			dest[count] = s;
			ofset = 1;
		}
		dest[count + ofset] = arr[count];
		count++;
	}
	if (ofset == 0)
		dest[count] = s;
	dest[count + 1] = NULL;
	free(arr);
	return (dest);
}

char	*ft_arrnstr(char **haystack, char *needle, int *index)
{
	int	len;

	*index = 0;
	len = ft_strlen(needle);
	while (haystack[*index])
	{
		if (ft_strnstr(haystack[*index], needle, len))
			return (haystack[*index]);
		*index += 1;
	}
	return (NULL);
}

void	ft_putarrs_fd(char **arr, int fd)
{
	while (*arr)
	{
		ft_putendl_fd(*arr, fd);
		arr++;
	}
}

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
