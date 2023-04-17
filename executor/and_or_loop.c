/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   and_or_loop.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 14:17:03 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/17 20:12:50 by jbax          ########   odam.nl         */
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
	// ft_putarrs_fd(bigdata->args, 1);
	bigdata->args = arr_expander(bigdata->args, super->env);
	// ft_putarrs_fd(bigdata->files, 1);
	bigdata->files = arr_expander(bigdata->files, super->env);
	while (bigdata)
	{
		if (bigdata->log_op == 1)
			what(bigdata, super);
		bigdata = bigdata->next;
	}
	(void)super;
	return (1);
}
