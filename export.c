/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 16:58:47 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/27 17:55:56 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "libft/libft.h"

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

char	*singlearg(char *arg, int *index)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	if (!arg[*index])
		return (NULL);
	i = *index;
	j = 1;
	k = 0;
	while (arg[*index] && j)
	{
		if (arg[*index] == '"')
			k++;
		if (arg[*index] == ' ' && (k % 2) == 0)
			j = 0;
		*index += 1;
	}
	if ((k % 2))
		return (NULL);
	dest = ft_calloc((*index - i) + 1, 1);
	ft_strlcpy(dest, &arg[i], (*index - i) + 1);
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
		temp = ft_lstnew(var);
		ft_lstadd_back(head, temp);
		var = singlearg(arg, &index);
	}
}

int ft_cmp(char **env, char *var)
{
	char	*t;
	char	*d;
	int		index;
	int		i;

	i = 0;
	var = ft_strdup(var);
	t = ft_strchr(var, '=');
	ft_bzero(t, 1);
	ft_putendl_fd(var, 1);
	d = ft_arrnstr(&env[i], var, &index);
	while (d)
	{
		d = ft_strdup(d);
		t = ft_strchr(d, '=');
		ft_putendl_fd(d, 1);
		ft_bzero(t, 1);
		ft_putendl_fd(d, 1);
		if (!ft_strncmp(var, d, ft_strlen(d)))
		{
			free(var);
			free(d);
			return (i + index);
		}
		i += index + 1;
		free(d);
		d = ft_arrnstr(&env[i], var, &index);
	}
	free(d);
	free(var);
	return (0);
}

char	**checkandadd(char **env, t_list *head)
{
	int	index;

	while (head)
	{
		index = ft_cmp(env, head->content);
		if (index)
			env = ft_arrdell_index(env, index, free);
		if (!ft_isdigit(*(char*)(head->content)))
			env = ft_arradd_index(env, head->content, 100);
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
		ft_put_env(*env,1);
		ft_lstclear(&head, ft_not_free);
	}
}
/*
export a=1 b=2 c=3

arg opdelen in **vars
[
	1. loop door string 
]
rekening met "" en spaties er in
check of het corect is ( niet beginnen me cijfer)
zoek of het al bestaat 
als ja verwijder
add de niewe var
*/