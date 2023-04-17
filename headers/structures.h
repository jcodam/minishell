/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structures.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 18:03:40 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/04/14 17:15:40 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "all.h"

typedef struct s_tokens
{
	char			*content;
	int				log_op;
	int				*mini_tok;
	char			**args;
	char			**files;
	int				*tokens;
	struct s_tokens	*next;
}	t_tokens;

enum	e_log_op
{
	OPP_AND = 1,
	OPP_OR,
	OPP_PIPE
};

enum e_commands
{
	OTHER = -1,
	SPC,
	REDIRECT_IP = 10,
	REDIRECT_OP,
	RD_TIL_DELIM,
	REDIRECT_APPEND,
	PIPE = 20,
	SPLIT_AND,
	SPLIT_OR,
	COMMAND = 30,
	FLAGS,
	FILE_T,
	QUOTE_DL,
	QUOTE_SL
};

// enum e_commands
// {
// 	OTHER = -1,
// 	QUOTE_SL,
// 	QUOTE_DL,
// 	REDIRECT_IP,
// 	REDIRECT_OP,
// 	RD_TIL_DELIM,
// 	REDIRECT_APPEND,
// 	COMMAND,
// 	PIPE,
// 	SPC,
// 	ENV_VAR,
// 	EXPANDABLE,
// 	FILE_T,
// 	SPLIT_AND,
// 	SPLIT_OR,
// 	FLAGS
// };

#endif
