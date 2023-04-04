/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   letspipe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 18:27:00 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/04 17:51:30 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../headers/all.h"
#include "../headers/signal_list.h"

int	what_cmd1(char **args, t_super *super, int pipes, int fd);

int	stage_files(char **files, int *tokens)
{
	int index;

	index = 0;
	while (files)
	{
		if (tokens[index] == REDIRECT_IP || tokens[index] == RD_TIL_DELIM)
			setfd_read(files[index]);
		else if (tokens[index] == REDIRECT_OP)
			setfd_write(files[index]);
		else if (tokens[index] == REDIRECT_APPEND)
			setfd_append(files[index]);
		index++;
	}
	return (0);
}

int	is_empty(char *line)
{
	while (*line && ft_iswhite_space(*line))
		line++;
	if (*line)
		return (1);
	return (0);
}

static void	set_exit_code(t_super *super, t_tokens *bigdata, int error)
{
	int	last_pipe;

	last_pipe = 0;
	if (!bigdata->next || bigdata->next->log_op != 3)
		last_pipe = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, super->term_struct);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, super->term_struct);
	tcsetattr(STDERR_FILENO, TCSAFLUSH, super->term_struct);
	if (last_pipe && error > 0 && error < 16)
	{
		ft_putendl_fd((char *)signals[error], 2);
		g_exit_code = (error + 128);
	}
	else if (last_pipe)
		g_exit_code = (error / 256);
	set_signal_parrent();
}

static int	mk_pipes(t_tokens *bigdata, int readfd, t_super *super)
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
		if (bigdata->next && bigdata->next->log_op == 3)
			dup2(pipefd[1], 1);
		stage_files(bigdata->args, bigdata->tokens);
		error = what_cmd1(bigdata->args, super, 1, 1);
		close(pipefd[1]);
		exit(error);
	}
	close(pipefd[1]);
	if (bigdata->next && bigdata->next->log_op == 3)
		mk_pipes(bigdata->next, pipefd[0], super);
	close(pipefd[0]);
	pid = waitpid(pid, &error, WCONTINUED);
	set_exit_code(super, bigdata, error); // pipes 0 = set exitcode
	return (1);
}

int	what_cmd2(t_tokens *bigdata, t_super *super)
{
	char			**cpipes;
	static int		stdio[2] = {0, 0};

	if (!bigdata->args || !bigdata->args[0])
		return (0);
	if (!stdio[0] || !stdio[1])
	{
		stdio[1] = dup(1);
		stdio[0] = dup(0);
	}
	if (bigdata->next && bigdata->next->log_op != 3)
	{
		stage_files(bigdata->files, bigdata->tokens);
		what_cmd1(bigdata->args, super, 0, 1);
		dup2(stdio[1], 1);
		dup2(stdio[0], 0);
		return (0);
	}
	block_signal();
	mk_pipes(bigdata, 0, super);
	set_signal_parrent();
	return (g_exit_code);
}

int	what(t_tokens *bigdata, t_super *super)
{
	what_cmd2(bigdata, super);
	while (bigdata)
	{
		if (g_exit_code && bigdata->log_op == 2)
		{
			what_cmd2(bigdata, super);
		}
		bigdata = bigdata->next;
	}
	return (1);
}

int	what_cmd(t_tokens *bigdata, t_super *super)
{
	while (bigdata)
	{
		if (bigdata->log_op == 1)
		what(bigdata, super);
		bigdata = bigdata->next;
	}
	(void)super;
	return (1);
}