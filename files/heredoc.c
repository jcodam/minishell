/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 15:13:23 by jbax          #+#    #+#                 */
/*   Updated: 2023/05/15 17:57:54 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"
#include <fcntl.h>
#include <errno.h>

static int	strsame(char *eoh, int leneof, char *line)
{
	int	len_line;

	len_line = ft_strlen(line);
	if (ft_strncmp(line, eoh, leneof))
		return (0);
	if (leneof != len_line)
		return (0);
	return (1);
}

static void	heredoc_loop(char *eoh, int leneof, int fd, t_super *env)
{
	char	**line;

	line = malloc(sizeof(char *) * 2);
	line[1] = NULL;
	line[0] = readline("> ");
	if (!line[0] || strsame(eoh, leneof, line[0]))
	{
		exit(0);
	}
	expend_vars(line, env->env);
	write(fd, line[0], ft_strlen(line[0]));
	write(fd, "\n", 1);
	ft_arrclear_c(line, 1);
	heredoc_loop(eoh, leneof, fd, env);
	exit(0);
}

static void	failed_heredoc(char **fdname, int sig)
{
	int	error;

	error = unlink(*fdname);
	if (error == -1)
		perror(*fdname);
	free(*fdname);
	*fdname = 0;
	if (WIFSIGNALED(sig))
		g_exit_code = 1;
	else
		g_exit_code = (sig / 256);
}

static int	mkchild(char *eoh, int fd, char **fdname, t_super *env)
{
	int			i;
	pid_t		id;

	id = fork();
	if (id == -1)
		exit_errbug("fork failed", "heredoc 50");
	if (!id)
	{
		set_signal_parrent('h');
		heredoc_loop(eoh, ft_strlen(eoh), fd, env);
	}
	waitpid(id, &i, 0);
	close(fd);
	free(eoh);
	if (i)
	{
		failed_heredoc(fdname, i);
		return (0);
	}
	return (1);
}

char	*heredoc(char *eoh, int tmpfindex, t_super *env)
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
				exit_errbug("heredoc failed", "heredoc");
		}
		else
		{
			mkchild(eoh, fd, &fdname, env);
			return (fdname);
		}
		tmpfindex++;
		free(fdname);
	}
	return (0);
}
