/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structures.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 18:03:40 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/03/07 16:17:11 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "all.h"

typedef struct s_tokens
{
	int				type;
	int				e_var_type;
	int				iter;
	int				section;
	char			*content;
	//char			*command;
	char			**args;
	char			**files;
	int				*tokens;
	struct s_tokens	*next;
}	t_tokens;

enum e_commands
{
	OTHER = -1,
	QUOTE_SL,
	QUOTE_DL,
	REDIRECT_IP,
	REDIRECT_OP,
	RD_TIL_DELIM,
	REDIRECT_APPEND,
	COMMAND,
	PIPE,
	SPC,
	ENV_VAR,
	EXPANDABLE,
	FILE_T,
	SPLIT_AND,
	SPLIT_OR
};

#endif