/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_data_struct.h                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/20 14:48:02 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/27 14:18:07 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_DATA_STRUCT_H
# define BUILTINS_DATA_STRUCT_H

typedef struct s_builtins
{
	char	*cmd;
	char	*options;
	char	*args;
}	t_builtins;

#endif