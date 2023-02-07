/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/29 14:35:03 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/07 13:49:15 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static char	**check_for_del(char **env, t_list *head)
{
	int	index;

	while (head)
	{
		index = ft_env_index(env, head->content);
		if (index != -1)
			env = ft_arrdell_index(env, index, free);
		head = head->next;
	}
	return (env);
}

void	ft_unset(char ***env, char *arg, int output_fd)
{
	t_list	*head;

	head = 0;
	arglist(&head, arg);
	*env = check_for_del(*env, head);
	ft_lstclear(&head, free);
	(void)output_fd;
}
