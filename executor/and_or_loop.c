/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   and_or_loop.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 14:17:03 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/12 14:20:31 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/all.h"

int	what_cmd2(t_tokens *bigdata, t_super *super);

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
