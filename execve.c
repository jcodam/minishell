/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 15:19:09 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/02 16:32:22 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "signal_list.h"

static int	execcmd(char **arg, t_super *super)
{
	int		i;
	int		index;
	char	*location;
	char	**path;

	location = ft_replacevar(ft_strdup("$PATH"), 0, super->env);
	path = ft_split(location, ':');
	i = execve(arg[0], &arg[0], super->env);
	index = 0;
	while (i == -1 && path && path[index])
	{
		free(location);
		location = ft_strjoin3(path[index], "/", arg[0]);
		i = execve(location, &arg[0], super->env);
		index++;
	}
	i = 127;
	ft_putstr_fd("minishel: ", 2);
	ft_putstr_fd(*arg, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (i);
}

static pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(0);
	return (pid);
}

void	ft_othercmd(char **arg, t_super *super, int ispipe, int fd)
{
	pid_t	pid;
	int		error;

	if (!ispipe)
	{
		block_signal();
		pid = ft_fork();
		if (pid == 0)
		{
			reset_signal();
			error = execcmd(arg, super);
			exit(error);
		}
		pid = waitpid(pid, &error, WCONTINUED);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, super->term_struct);
		tcsetattr(STDOUT_FILENO, TCSAFLUSH, super->term_struct);
		tcsetattr(STDERR_FILENO, TCSAFLUSH, super->term_struct);
		if (error > 0 && error < 16)
		{
			printf("%s\n", signals[error]);
			g_exit_code = (error + 128);
		}
		else
			g_exit_code = (error / 256);
		set_signal_parrent();
	}
	else
	{
		error = execcmd(arg, super);
		exit(error);
	}
	(void)fd;
}
/* 131 ctr \ 127 no cmt */
// printf("\n%d\n", WEXITSTATUS(error));
