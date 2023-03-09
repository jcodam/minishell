/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 15:13:23 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/08 16:08:22 by jbax          ########   odam.nl         */
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
		// sleep(1);
		// ft_putendl_fd(&line[i], 2);
	}
	fdname = ft_substr(line, 0, i);
	if (!fdname)
		exit_errbug("malloc fail", "making fdname");
	i = open(fdname, O_RDONLY);
	free(fdname);
	if (i == -1)
	{
		ft_putendl_fd("not open file", 2);
		return 0;
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
		// sleep(1);
		// ft_putendl_fd(&line[i], 2);
	}
	fdname = ft_substr(line, 0, i);
	if (!fdname)
		exit_errbug("malloc fail", "making fdname");
	i = open(fdname, O_WRONLY | O_TRUNC);
	free(fdname);
	if (i == -1)
	{
		ft_putendl_fd("not open file", 2);
		return 0;
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
		// sleep(1);
		// ft_putendl_fd(&line[i], 2);
	}
	fdname = ft_substr(line, 0, i);
	if (!fdname)
		exit_errbug("malloc fail", "making fdname");
	i = open(fdname, O_WRONLY | O_APPEND);
	free(fdname);
	if (i == -1)
	{
		ft_putendl_fd("not open file", 2);
		return 0;
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
				// sleep(1);
				// ft_putendl_fd(*line, 2);
			}
		}
		else if (**line == '>' && line[0][1] == '>')
		{
			*line += 2;
			tmpopena(*line);
			while (ft_isalnum(**line) || **line == '.')
			{
				*line += 1;
				// sleep(1);
				// ft_putendl_fd(*line, 2);
			}
		}
		else if (**line == '>')
		{
			*line += 1;
			tmpopenw(*line);
			while (ft_isalnum(**line) || **line == '.')
			{
				*line += 1;
				// sleep(1);
				// ft_putendl_fd(*line, 2);
			}
		}
		// else if (**line == '>')
		// else if (**line == '>>')
		else
			*line += 1;
	}
	// ft_putendl_fd(*line, 2);
	return 0;
}
