/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 15:13:23 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/20 14:15:52 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include <fcntl.h>

// sheredoc

int tmpopen(char *line)
{
	int		i;
	char	*fdname;

	i = 0;
	while (ft_isalnum(line[i]) || line[i] == '.')
	{
		i++;
	}
	fdname = ft_substr(line, 0, i);
	if (!fdname)
		exit_errbug("malloc fail", "making fdname");
	i = open(fdname, O_RDONLY);
	free(fdname);
	if (i == -1)
	{
		ft_putendl_fd("not open file", 2);
		return (0);
	}
	dup2(i, 0);
	close(i);
	return (0);
}

int tmpopenw(char *line)
{
	int		i;
	char	*fdname;

	i = 0;
	while (ft_isalnum(line[i]) || line[i] == '.')
	{
		i++;
	}
	fdname = ft_substr(line, 0, i);
	if (!fdname)
		exit_errbug("malloc fail", "making fdname");
	i = open(fdname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	free(fdname);
	if (i == -1)
	{
		ft_putendl_fd("not open file", 2);
		return (0);
	}
	dup2(i, 1);
	close(i);
	return (0);
}

int tmpopena(char *line)
{
	int		i;
	char	*fdname;

	i = 0;
	while (ft_isalnum(line[i]) || line[i] == '.')
	{
		i++;
	}
	fdname = ft_substr(line, 0, i);
	if (!fdname)
		exit_errbug("malloc fail", "making fdname");
	i = open(fdname, O_WRONLY | O_APPEND | O_CREAT, 0644);
	free(fdname);
	if (i == -1)
	{
		ft_putendl_fd("not open file", 2);
		return (0);
	}
	dup2(i, 1);
	close(i);
	return (0);
}

int	tmpfileswitch(char **line)
{
	while (**line && !ft_isalnum(**line))
	{
		if (**line == '<')
		{
			*line += 1;
			tmpopen(*line);
			while (ft_isalnum(**line) || **line == '.')
			{
				*line += 1;
			}
		}
		else if (**line == '>' && line[0][1] == '>')
		{
			*line += 2;
			tmpopena(*line);
			while (ft_isalnum(**line) || **line == '.')
			{
				*line += 1;
			}
		}
		else if (**line == '>')
		{
			*line += 1;
			tmpopenw(*line);
			while (ft_isalnum(**line) || **line == '.')
			{
				*line += 1;
			}
		}
		else
			*line += 1;
	}
	return (0);
}

/*
The following example uses the open() function to try to create the LOCKFILE file and open it for writing. Since the open() function specifies the O_EXCL flag, the call fails if the file already exists. In that case, the program assumes that someone else is updating the password file and exits.

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define LOCKFILE "/etc/ptmp"
...
int pfd; Integer for file descriptor returned by open() call.
...
if ((pfd = open(LOCKFILE, O_WRONLY | O_CREAT | O_EXCL,
    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
{
    fprintf(stderr, "Cannot open /etc/ptmp. Try again later.\n");
    exit(1);
}
...
*/