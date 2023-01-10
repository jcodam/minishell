/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:49:07 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/10 18:37:39 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
	
void 	rl_clear_history(void);
void	rl_replace_line (const char *, int );
#define empty 1
#define full 0
/* 
char *var = read_the_line()
wil wait for and return the line
*/
int	empty_line(char *line)
{
	if (!line)
		return (empty);
	while (*line)
	{
		if (*line > 32)
			return (full);
		line++;
	}
	return (empty);
}
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
		(void)signum;
		rl_replace_line("", 0);
		rl_redisplay();
		printf("\n");
		rl_on_new_line();
	}
	if (signum == SIGQUIT)
	{
		exit(1);
	}
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
		printf("type your comment bellow;%d\n", i);
		line = read_the_line();
		system(line);
		if (empty_line(line) == full)
			add_history(line);
		if (i == 4)
		{
			rl_clear_history();
			i = 0;
		}
		i++;
		free(line);
	}
	return (0);
}

// rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,