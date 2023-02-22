/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 17:05:02 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/22 18:13:32 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "builtins_data_struct.h"

char	**copy_env(char **env)
{
	int		len;
	char	**dest;

	len = ft_arrlen_c(env);
	dest = ft_arrdup_c(env, len);
	if (!dest)
		exit(0);
	return (dest);
}

char	*ft_env_name(char *env)
{
	char	*temp;

	env = ft_strdup(env);
	if (!env)
		exit(1);
	temp = ft_strchr(env, '=');
	if (temp)
		ft_bzero(temp, 1);
	return (env);
}

char	*ft_env_content(char *env)
{
	char	*temp;

	temp = ft_strchr(env, '=');
	if (!temp)
	{
		env = ft_strdup("");
		return (env);
	}
	env = ft_strdup(&temp[1]);
	return (env);
}

int	ft_env_index(char **env, char *var)
{
	char	*d;
	int		index;
	int		i;

	i = 0;
	var = ft_env_name(var);
	d = ft_arrnstr(&env[i], var, &index);
	while (d)
	{
		d = ft_env_name(d);
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
	return (-1);
}

void	ft_put_env(t_super *super, int fd)
{
	char	**env;

	env = super->env;
	super->exit_code = 0;
	while (*env)
	{
		if (ft_strchr(*env, '='))
			ft_putendl_fd(*env, fd);
		env++;
	}
}

char	*ft_getvar(char *ptr, char **env)
{
	int		i;
	char	*str;

	i = 0;
	while (ft_isalnum(ptr[i]) || ptr[i] == '_')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, ptr, i + 1);
	i = ft_env_index(env, str);
	free(str);
	if (i != -1)
		str = ft_env_content(env[i]);
	else
		return (ft_strdup(""));
	return (str);
}

char	*ft_replacevar(char *head, int index, char **env)
{
	char	*tmp[3];

	tmp[0] = ft_strdup(head);
	if (!tmp[0])
		exit(0);
	tmp[0][index] = 0;
	index++;
	tmp[1] = ft_getvar(&head[index], env);
	if (!tmp[1])
		exit(0);
	tmp[2] = ft_strjoin(tmp[0], tmp[1]);
	if (!tmp[2])
		exit(0);
	free(tmp[0]);
	free(tmp[1]);
	if (ft_isdigit(head[index]))
		index++;
	else
	{
		while (ft_isalnum(head[index]) || head[index] == '_')
			index++;
	}
	tmp[0] = ft_strjoin(tmp[2], &head[index]);
	if (!tmp[0])
		exit(0);
	free(tmp[2]);
	free(head);
	return (tmp[0]);
}
