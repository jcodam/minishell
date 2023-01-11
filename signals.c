/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:42:30 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/11 14:59:41 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	sighandler_parent(int signum)
{
	if (signum == SIGINT)
	{
		(void)signum;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		rl_clear_history();
	}
}

void	set_signal_parrent(void)
{
	struct sigaction	sagnal_struct;

	sagnal_struct.sa_flags = SA_RESTART;
	sagnal_struct.__sigaction_u.__sa_handler = &sighandler_parent;
	sigaction(SIGINT, &sagnal_struct, NULL);
	sigaction(SIGQUIT, &sagnal_struct, NULL);
}
