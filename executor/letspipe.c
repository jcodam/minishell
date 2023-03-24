/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   letspipe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 18:27:00 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/22 18:39:42 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"
#include "../headers/signal_list.h"

int	what_cmd1(char *line, t_super *super, int pipes, int fd);

int	is_empty(char *line)
{
	while (*line && ft_iswhite_space(*line))
		line++;
	if (*line)
		return (1);
	return (0);
}

static char	**splitpipe(char *line, int *p)
{
	char	**args;
	int		j;

	j = 0;
	args = ft_split(line, '|');
	if (!args)
		return (0);
	while (args[j])
	{
		if (!is_empty(args[j]))
			args = ft_arrdell_index(args, j, free);
		else
			j++;
	}
	*p = j - 1;
	return (args);
}

static void	ll(t_super *super, int pipes, int error)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, super->term_struct);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, super->term_struct);
	tcsetattr(STDERR_FILENO, TCSAFLUSH, super->term_struct);
	if (!pipes && error > 0 && error < 16)
	{
		ft_putendl_fd((char *)signals[error], 2);
		g_exit_code = (error + 128);
	}
	else if (!pipes)
		g_exit_code = (error / 256);
	set_signal_parrent();
}

static int	mk_pipes(char **cpipes, int readfd, t_super *super, int pipes)
{
	int		pipefd[2];
	pid_t	pid;
	int		error;

	error = pipe(pipefd);
	if (error == -1)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		reset_signal();
		close(pipefd[0]);
		dup2(readfd, 0);
		if (pipes)
			dup2(pipefd[1], 1);
		// in progres .....
		error = what_cmd1(*cpipes, super, 1, 1);
		close(pipefd[1]);
		exit(error);
	}
	close(pipefd[1]);
	if (pipes)
		mk_pipes(cpipes + 1, pipefd[0], super, pipes - 1);
	close(pipefd[0]);
	pid = waitpid(pid, &error, WCONTINUED);
	ll(super, pipes, error);
	return (1);
}

int	what_cmd(char *line, t_super *super)
{
	int				pipes;
	char			**cpipes;
	static int		stdio[2] = {0, 0};

	if (!line | !is_empty(line))
		return (0);
	if (!stdio[0] || !stdio[1])
	{
		stdio[1] = dup(1);
		stdio[0] = dup(0);
	}
	pipes = 0;
	cpipes = splitpipe(line, &pipes);
	if (!pipes)
	{
		ft_arrclear_c(cpipes, ft_arrlen_c(cpipes));
		what_cmd1(line, super, 0, 1);
		dup2(stdio[1], 1);
		dup2(stdio[0], 0);
		return (0);
	}
	block_signal();
	mk_pipes(cpipes, 0, super, pipes);
	set_signal_parrent();
	ft_arrclear_c(cpipes, ft_arrlen_c(cpipes));
	return (g_exit_code);
}
