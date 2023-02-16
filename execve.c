/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 15:19:09 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/16 17:19:39 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int	execcmd(char **arg, t_super *super, int fd)
{
	int		i = 5;
	char	*location;

	// ft_putarrs_fd(arg, 2);
	i = execve(arg[0], &arg[0], super->env);
	// ft_putnbr_fd(i, 1);
	if (i == -1)
	{
		location = ft_strjoin("/bin/", arg[0]);
		i = execve(location, &arg[0], super->env);
		// ft_putnbr_fd(i, 1);
		if (i == -1)
		{
			free(location);
			location = ft_strjoin("/usr/bin/", arg[0]);
			i = execve(location, &arg[0], super->env);
			// ft_putnbr_fd(i, 1);
			if (i == -1)
				i = 127;
		}
		free(location);
	}
	ft_putstr_fd("minishel: ", fd);
	ft_putstr_fd(*arg, fd);
	ft_putstr_fd(": command not found\n", fd);
	return (i);
}

//fs: command not found  
pid_t	ft_fork()
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
			error = execcmd(arg, super, fd);
			printf("%d\n", error);
			exit(-2);
		}
		pid = waitpid(pid, &error, WCONTINUED);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, super->term_struct);
		tcsetattr(STDOUT_FILENO, TCSAFLUSH, super->term_struct);
		tcsetattr(STDERR_FILENO, TCSAFLUSH, super->term_struct);
		if (error == 3)
			printf("\n");
		printf("%d\n", error);
		// printf("\n%s\n", rl_prompt);
		set_signal_parrent();
	}
}
/* 131 ctr \ 127 no cmt */
// int main(int argc, char *argv[], char **envl)
// {
// 	int i = 0;
// 	char	*location;

// 	ft_putarrs_fd(argv, 2);
// 	i = execve(argv[1], &argv[1], envl);
// 	ft_putnbr_fd(i, 1);
// 	if (i == -1)
// 	{
// 		location = ft_strjoin("/bin/", argv[1]);
// 		i = execve(location, &argv[1], envl);
// 		ft_putnbr_fd(i, 1);
// 		if (i == -1)
// 		{
// 			free(location);
// 			location = ft_strjoin("/usr/bin/", argv[1]);
// 			i = execve(location, &argv[1], envl);
// 			ft_putnbr_fd(i, 1);
// 		}
// 		free(location);
// 	}
// 	return 0;
// }
