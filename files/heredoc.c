/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 15:13:23 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/12 15:42:24 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"
#include <fcntl.h>
#include <errno.h>

static void	heredoc_loop(char *eoh, int leneof, int fd)
{
	char	*line;

	line = NULL;
	line = readline("> ");
	if (!line || !ft_strncmp(line, eoh, leneof))
	{
		exit(0);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	heredoc_loop(eoh, leneof, fd);
	exit(0);
}

static void	mkchild(char *eoh, int fd)
{
	int			i;
	pid_t		id;

	id = fork();
	if (id == -1)
		exit_errbug("fork failed", "heredoc 50");
	if (!id)
		heredoc_loop(eoh, ft_strlen(eoh), fd);
	waitpid(id, &i, 0);
	if (WIFSIGNALED(i))
		printf("%d\n", WIFSIGNALED(i));
	close(fd);
	free(eoh);
}

char	*heredoc(char *eoh, int tmpfindex)
{
	static char	*basename = ".tempdir/.tmpfile_heredoc_";
	char		*fdname;
	int			fd;
	char		*num;

	while (tmpfindex)
	{
		num = ft_itoa(tmpfindex);
		fdname = ft_strjoin(basename, num);
		free(num);
		fd = open(fdname, O_RDWR | O_CREAT | O_EXCL, 0644);
		if (fd == -1)
		{
			if (errno != EEXIST)
				exit_errbug("heredoc failed", "heredoc 50");
		}
		else
		{
			mkchild(eoh, fd);
			return (fdname);
		}
		tmpfindex++;
		free(fdname);
	}
	return (0);
}

// /*temp*/
// int	start_heredoc(char *line)
// {
// 	int		i;
// 	char	*fdname;

// 	i = 0;
// 	while (ft_isalnum(line[i]) || line[i] == '.' || line[i] == '_')
// 	{
// 		i++;
// 	}
// 	fdname = ft_substr(line, 0, i);
// 	if (!fdname)
// 		exit_errbug("malloc fail", "making fdname");
// 	line = heredoc(fdname, 1);
// 	i = open(line, O_RDONLY);
// 	free(line);
// 	if (i == -1)
// 	{
// 		ft_putendl_fd("not open file", 2);
// 		return (0);
// 	}
// 	dup2(i, 0);
// 	close(i);
// 	return (0);
// }

// /*temp*/
// int	tmpfileswitch(char **line)
// {
// 	while (**line && !ft_isalnum(**line) && **line != '$')
// 	{
// 		if (**line == '<' && line[0][1] == '<')
// 		{
// 			*line += 2;
// 			while (**line == ' ')
// 				*line += 1;
// 			start_heredoc(*line);
// 			while (ft_isalnum(**line) || **line == '.' || **line == '_')
// 			{
// 				*line += 1;
// 			}
// 		}
// 		else if (**line == '<')
// 		{
// 			*line += 1;
// 			while (**line == ' ')
// 				*line += 1;
// 			setfd_read(*line);
// 			while (ft_isalnum(**line) || **line == '.' || **line == '_')
// 			{
// 				*line += 1;
// 			}
// 		}
// 		else if (**line == '>' && line[0][1] == '>')
// 		{
// 			*line += 2;
// 			while (**line == ' ')
// 				*line += 1;
// 			setfd_append(*line);
// 			while (ft_isalnum(**line) || **line == '.' || **line == '_')
// 			{
// 				*line += 1;
// 			}
// 		}
// 		else if (**line == '>')
// 		{
// 			*line += 1;
// 			while (**line == ' ')
// 				*line += 1;
// 			setfd_write(*line);
// 			while (ft_isalnum(**line) || **line == '.' || **line == '_')
// 			{
// 				*line += 1;
// 			}
// 		}
// 		else
// 			*line += 1;
// 	}
// 	return (0);
// }
