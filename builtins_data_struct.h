/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_data_struct.h                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/20 14:48:02 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/08 12:10:18 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_DATA_STRUCT_H
# define BUILTINS_DATA_STRUCT_H

#include "all.h"

typedef struct s_arglist
{
	char				**arg;
	struct s_arglist	*next;
}	t_arglist;

typedef struct s_super
{
	char	**env;
	int		exit_code;
}	t_super;

#endif