/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:49:07 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/10 14:34:50 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void 	rl_clear_history(void);
// char *var = read_the_line()
// wil wait for and return the line
char	*read_the_line(void)
{
	char	*line;

	line = NULL;
	while (!line)
		line = readline(0);
	return (line);
}

static void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line();
		rl_redisplay();
		exit(1);
	}
	if (signum == SIGQUIT)
	{}
	// if (signum ==)

}

int	main(void)
{
	char	*line;
	int		i = 0;
	struct sigaction sa;

	sa.sa_flags = SA_RESTART;
	sa.__sigaction_u.__sa_handler = &sighandler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	// sigaction(, &sa, NULL);

	while (1)
	{
		line = read_the_line();
		printf("%s   %d\n", line, i);
		system(line);
		if (line[1])
			add_history(line);
		if (i == 3)
		{
			printf("\n");
			rl_on_new_line();
			// rl_replace_line();
			rl_redisplay();
		}
		if (i == 4)
		{
			// rl_clear_history();
			i = 0;
		}
		i++;
		free(line);
	}
	return (0);
}

// rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,