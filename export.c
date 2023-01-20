/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 16:58:47 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/20 21:18:02 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	ft_lstputs_fd(t_list *head, int fd)
{
	if (!head)
		return (0);
	while (head)
	{
		ft_putendl_fd(head->content, fd);
		head = head->next;
	}
	return (1);
}

void	ft_lstinsert(t_list **head, t_list *new, int index)
{
	int		i;
	t_list	*temp;

	if (index <= 0)
		ft_lstadd_front(head, new);
	else
	{
		if (!(*head))
			*head = new;
		else
		{
			i = 0;
			temp = *head;
			while (temp && i < index - 1)
			{
				temp = temp->next;
				i++;
			}
			new->next = temp->next;
			temp->next = new;
		}
	}
}

void	ft_lstadd_ascii(t_list **head, t_list *new)
{
	t_list	*temp;
	int		i;
	int		len;

	if (!(*head))
		*head = new;
	else
	{
		i = 0;
		len = ft_strlen(new->content);
		temp = *head;
		while (i != -1 && temp)
		{
			int k = ft_strncmp(temp->content, new->content, len);
			if (k >= 0)
			{
				ft_lstinsert(head, new, i);
				i = -1;
			}
			else
			{
				temp = temp->next;
				i++;
			}
		}
		if (i != -1)
			ft_lstadd_back(head, new);
	}
}

t_list	*ft_lstnew_ascii(char **arr)
{
	int count;
	t_list *new;
	t_list *head;

	count = 0;
	head = 0;
	while (arr[count])
	{
		new = ft_lstnew(arr[count]);
		ft_lstadd_ascii(&head, new);
		count++;
		// ft_lstputs_fd(head, 1);
	}

	return (head);
}

void	ft_export_no_arguments(char **env, int output_fd)
{
	t_list	*head;

	head = ft_lstnew_ascii(env);
	ft_lstputs_fd(head, output_fd);
	(void)output_fd;
}
