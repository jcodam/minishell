/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:46:19 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/09 18:01:10 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "all.h"
#define ERROR 0
#define FOUND 1
#define NOT_FOUND 0

// int wild(char )

int	strcmpwild(char *card, char *s)
{
	while (*card)// comper
	{
		if (!*s && *card && *card != '*')
			return (NOT_FOUND);
		if (*card == '*') // na ster == s
		{
			while (*card == '*')
				card++;
			if (!*card)
				return (FOUND);
			while (*s)
			{
				while (*s && *card != *s) // go tot gelijk aan
					s++;
				if (strcmpwild(card, s))
					return (FOUND);
				if (*s)
					s++;
			}
			if (!*s)
				return (NOT_FOUND);
		}
		else if (*card == *s)
		{
			card++;
			s++;
		}
		else
		{
			return (NOT_FOUND);
		}
	}
	if (!*s && !*card)
		return (FOUND);
	return (NOT_FOUND);
}

char	**get_wildcard(char *wild)
{
	DIR				*dirp;
	struct dirent	*dp;
	size_t			len;

	dirp = opendir("./fucking_around");
	if (dirp == 0)
			return (ERROR);
	len = strlen(wild);
	while ((dp = readdir(dirp)) != 0)
	{
		ft_putendl_fd(dp->d_name, 1);
		if (strcmpwild(wild, dp->d_name))
			write(1,"FOUND\n\n",7);
			// ft_putendl_fd("FOUND\n", 1);
			// if (dp->d_namlen == len && strcmp(dp->d_name, name) == 0) {
			// 		(void)closedir(dirp);
			// 		return (FOUND);
			// }
	}
	(void)closedir(dirp);
	return (NOT_FOUND);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_putnbr_fd(argc, 1);
		for (int i = 0; i < argc ; i++)
			ft_putendl_fd(argv[i], 1);
		return 0;
	}
	char **card;
	card = get_wildcard(argv[1]);
	while (card && *card)
	{
		ft_putendl_fd(*card, 1);
		card++;
	}
	// free(card);
	return 0;
}
