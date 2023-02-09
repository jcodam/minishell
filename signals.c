/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:42:30 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/09 17:35:03 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	sighandler_parent(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		rl_clear_history();
		exit(0);
	}
}

void	set_signal_parrent(void)
{
	signal(SIGINT, sighandler_parent);
	signal(SIGQUIT, sighandler_parent);
}

void	block_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

// {
// 	struct sigaction	sagnal_struct;

// 	sagnal_struct.sa_flags = SA_RESTART;
// 	sagnal_struct.__sigaction_u.__sa_handler = &sighandler_parent;
// 	sigaction(SIGINT, &sagnal_struct, NULL);
// 	sigaction(SIGQUIT, &sagnal_struct, NULL);
// }
