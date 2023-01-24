/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 16:58:47 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/24 17:30:29 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	ft_export_no_arguments(char **env, int output_fd)
{
	t_list	*head;

	head = ft_lstnew_ascii(env);
	if (!head)
		exit(1);
	ft_lstput_promts_fd(head, "declare -x ", output_fd);
	(void)output_fd;
	ft_lstclear(&head, ft_not_free);
}
