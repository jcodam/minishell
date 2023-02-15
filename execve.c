/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 15:19:09 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/15 17:55:23 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	execcmd(char **arg, t_super *super)
{
	int		i = 0;
	char	*location;

	ft_putarrs_fd(arg, 2);
	i = execve(arg[0], &arg[0], super->env);
	ft_putnbr_fd(i, 1);
	if (i == -1)
	{
		location = ft_strjoin("/bin/", arg[0]);
		i = execve(location, &arg[0], super->env);
		ft_putnbr_fd(i, 1);
		if (i == -1)
		{
			free(location);
			location = ft_strjoin("/usr/bin/", arg[0]);
			i = execve(location, &arg[0], super->env);
			ft_putnbr_fd(i, 1);
		}
		free(location);
	}
}

pid_t	ft_fork()
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(0);
	return (pid);
}

void	ft_othercmd(char **arg, t_super *super, int ispipe)
{
	pid_t	pid;
	int		error;

	printf("test\n");
	if (!ispipe)
	{
		printf("test\n");
		pid = ft_fork();
		if (pid == 0)
		{
			printf("test\n");
			execcmd(arg, super);
			printf("test\n");
			exit(0);
		}
		pid = waitpid(pid, &error, WUNTRACED);
	}
}

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
