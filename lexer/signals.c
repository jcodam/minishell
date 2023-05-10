/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:42:30 by jbax          #+#    #+#                 */
/*   Updated: 2023/05/10 15:00:05 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

void	sighandler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 2);
		exit(1);
	}
}

void	sighandler_parent(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 2);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 1;
	}
}

void	set_signal_parrent(char set)
{
	if (set == 'p')
	{
		signal(SIGINT, sighandler_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	if (set == 'h')
	{
		signal(SIGINT, sighandler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	block_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
