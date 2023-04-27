/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_variations.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 17:46:08 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/04/26 17:49:51 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

int	ar_len(int *arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (0);
	while (arr[len] != EOL)
		len++;
	return (len);
}

int	*ms_arrdup(int *arr, int len)
{
	int	*newarr;
	int	i;

	i = 0;
	if (!arr || !len)
		return (NULL);
	newarr = malloc(sizeof(int) * len);
	while (i <= len)
	{
		newarr[i] = arr[i];
		i++;
	}
	newarr[i] = -2;
	return (newarr);
}

int	*ft_subarr(int *arr, size_t start, size_t len)
{
	size_t			i;
	int				*newarr;
	size_t			arrlen;

	i = 0;
	if (!arr)
		return (0);
	arrlen = ar_len(arr);
	if (start > arrlen)
		return (0);
	newarr = calloc_array((len + 2), -2);
	if (!newarr)
	{
		printf("\n malloc error!\n");
		return (NULL);
	}
	while (i <= len)
	{
		newarr[i] = arr[start + i];
		i++;
	}
	newarr[i] = -2;
	return (newarr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*newstr;
	size_t			strlen;

	i = 0;
	if (s == 0)
		return (NULL);
	strlen = ft_strlen(s);
	if (start > strlen)
		return (ft_strdup(""));
	if (len > strlen - start)
		return (ft_strdup(s + start));
	newstr = (char *)malloc(len + 2);
	if (newstr == 0)
	{
		printf("\n malloc error!\n");
		return (NULL);
	}
	while (i <= len)
	{
		newstr[i] = s[start + i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
