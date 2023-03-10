/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_data_struct.h                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/20 14:48:02 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/02 17:17:49 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_DATA_STRUCT_H
# define BUILTINS_DATA_STRUCT_H

typedef struct s_arglist
{
	char				**arg;
	struct s_arglist	*next;
}	t_arglist;

typedef struct s_super
{
	char			**env;
	struct termios	*term_struct;
}	t_super;

#endif