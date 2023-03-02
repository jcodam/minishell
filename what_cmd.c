/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   what_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 18:03:43 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/02 16:43:26 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int	look_for_cmd(char *line, int *found, char *commend)
{
	char	*cmd = 0;
	cmd = ft_strnstr(line, commend, 9);
	if (!cmd)
		return (0);
	*found += 1;
	return (1);
}

static char **mkarg(char *line)
{
	char	**args;
	int		i = 0;
	char	*temp;

	args = malloc(1 * sizeof(char *));
	args[0] = 0;
	temp = singlearg(line, &i);
	while (temp)
	{
		if (*temp)
			args = ft_arradd_index(args, temp, 100);
		temp = singlearg(line, &i);
	}
	// ft_putarrs_fd(args, 1);
	return (args);
}

int	what_cmd1(char *line, t_super *super, int pipes, int fd)
{
	int		found;
	char	**args;

	found = 0;
	args = mkarg(line);
	if (look_for_cmd(*args, &found, "$?") && ft_arrlen_c(args) == 1)
	{
		printf("%d\n", g_exit_code);
		g_exit_code = 0;
		return 0;
	}
	g_exit_code = 0;
	if (look_for_cmd(*args, &found, "pwd"))
	{
		ft_pwd(fd);
	}
	else if (look_for_cmd(*args, &found, "exit"))
		ft_exit_builtin(args);
	else if (look_for_cmd(*args, &found, "cd"))
		ft_change_dir(args[1]);
	else if (look_for_cmd(*args, &found, "env"))
	{
		ft_put_env(super, fd);
	}
	else if (look_for_cmd(*args, &found, "echo"))
	{
		ft_echo(args + 1, fd);
	}
	else if (look_for_cmd(*args, &found, "export"))
		ft_export(super, args, fd);
	else if (look_for_cmd(*args, &found, "unset"))
		ft_unset(super, args);
	else if (look_for_cmd(*args, &found, "var") && ft_arrlen_c(args) == 2)
		printf("%s\n", ft_getvar(args[1], super->env));
	else if (look_for_cmd(*args, &found, "lll"))
		printf("%s\n", ft_replacevar(ft_strdup(line), 3, super->env));
	else
		ft_othercmd(args, super, pipes, fd);
	ft_arrclear_c(args, ft_arrlen_c(args));
	return (found);
}

int ll(char *line)
{
	while (*line && ft_iswhite_space(*line))
		line++;
	if (*line)
		return (1);
	return (0);
}

static char **m_arg(char *line, int *p)
{
	char	**args;
	int		j = 0;

	args = ft_split(line, '|');
	if (!args)
		return (0);
	// ft_putarrs_fd(args, 1);
	while (args[j])
	{
		if (!ll(args[j]))
			args = ft_arrdell_index(args, j, free);
		else
			j++;
	}
	// ft_putarrs_fd(args, 1);
	*p = j - 1;
	return (args);
}

int	what_cmd2(char *line, t_super *super)
{
	// printf("%s\n", line);
	return (what_cmd1(line, super, 0, 1));
}
int	mk_pipes(char **cpipes, int readfd, t_super *super, int pipes)
{
	int	pipefd[2];
	pid_t pid;
	int	error;

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
		error = what_cmd1(*cpipes, super, 1, 1);
		close(pipefd[1]);
		exit(error);
	}
	close(pipefd[1]);
	if (pipes)
	{
		mk_pipes(cpipes + 1, pipefd[0], super, pipes - 1);
	}
	close(pipefd[0]);
	pid = waitpid(pid, &error, WCONTINUED);
	return (1);
}
int	what_cmd(char *line, t_super *super)
{
	int	pipes;
	char **cpipes;

	if (!line | !ll(line))
		return (0);
	pipes = 0;
	cpipes = m_arg(line, &pipes);//export , grep 'home' , null,; pipes = 2
	// printf("%d\n", pipes);
	if (!pipes)
	{
		ft_arrclear_c(cpipes, ft_arrlen_c(cpipes));
		return (what_cmd1(line, super, 0, 1));
	}
	block_signal();
	mk_pipes(cpipes, 0, super, pipes);
	set_signal_parrent();
	ft_arrclear_c(cpipes, ft_arrlen_c(cpipes));
	return (g_exit_code);
}
