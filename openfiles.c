/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   openfiles.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 12:49:00 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/22 13:51:26 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include <fcntl.h>
#include <errno.h>

int	setfd_read(char *filename)
{
	int		i;
	char	*fdname;

	i = 0;
	while (ft_isalnum(filename[i]) || filename[i] == '.' || filename[i] == '_')
	{
		i++;
	}
	fdname = ft_substr(filename, 0, i);
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
	return (1);
}

int	setfd_write(char *filename)
{
	int		i;
	char	*fdname;

	i = 0;
	while (ft_isalnum(filename[i]) || filename[i] == '.' || filename[i] == '_')
	{
		i++;
	}
	fdname = ft_substr(filename, 0, i);
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
	return (1);
}

int	setfd_append(char *filename)
{
	int		i;
	char	*fdname;

	i = 0;
	while (ft_isalnum(filename[i]) || filename[i] == '.' || filename[i] == '_')
	{
		i++;
	}
	fdname = ft_substr(filename, 0, i);
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
	return (1);
}
