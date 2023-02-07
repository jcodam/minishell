/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 16:58:47 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/07 13:48:59 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "libft/libft.h"

void	ft_put_export(t_list *envl, int fd)
{
	char	*s;

	while (envl)
	{
		ft_putstr_fd("declare -x ", fd);
		s = ft_env_name(envl->content);
		ft_putstr_fd(s, fd);
		free(s);
		if (ft_strchr(envl->content, '='))
		{
			ft_putstr_fd("=\"", fd);
			s = ft_env_content(envl->content);
			ft_putstr_fd(s, fd);
			ft_putstr_fd("\"", fd);
			free(s);
		}
		ft_putstr_fd("\n", fd);
		envl = envl->next;
	}
}

void	ft_export_no_arguments(char **env, int output_fd)
{
	t_list	*head;

	head = ft_lstnew_ascii(env);
	if (!head)
		exit(1);
	ft_put_export(head, output_fd);
	(void)output_fd;
	ft_lstclear(&head, ft_not_free);
}

char	*singlearg(char *arg, int *index)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	if (!arg[*index])
		return (NULL);
	i = *index;
	j = 0;
	k = 0;
	while (arg[*index] && !j)
	{
		if (arg[*index] == '"')
			k++;
		if (ft_iswhite_space(arg[*index]) && (k % 2) == 0)
			j = 1;
		*index += 1;
	}
	if ((k % 2))
		return (NULL);
	if (ft_iswhite_space(arg[i]))
		return ("\0");
	dest = ft_calloc((*index - i) + 1, 1);
	ft_strlcpy(dest, &arg[i], (*index - i - j) + 1);
	return (dest);
}

void	arglist(t_list **head, char *arg)
{
	t_list	*temp;
	int		index;
	char	*var;

	index = 0;
	var = singlearg(arg, &index);
	while (var)
	{
		if (var && *var)
		{
			temp = ft_lstnew(var);
			ft_lstadd_back(head, temp);
		}
		var = singlearg(arg, &index);
	}
}

char	**checkandadd(char **env, t_list *head)
{
	int	index;

	while (head)
	{
		index = ft_env_index(env, head->content);
		if (index != -1)
			env = ft_arrdell_index(env, index, free);
		if (!ft_isdigit(*(char *)(head->content)))
			env = ft_arradd_index(env, head->content, 100);
		else
			free(head->content);
		head = head->next;
	}
	return (env);
}

void	ft_export(char ***env, char *arg, int output_fd)
{
	t_list	*head;

	head = 0;
	if (!arg || !*arg)
		ft_export_no_arguments(*env, output_fd);
	else
	{
		arglist(&head, arg);
		*env = checkandadd(*env, head);
		ft_lstclear(&head, ft_not_free);
	}
}
