/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structures.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 18:03:40 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/03/31 17:34:42 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "all.h"

typedef struct s_tokens
{
	int				type;
	int				e_var_type;
	int				section;
	char			*content;
	int				log_op;
	int				has_pipe;
	int				*mini_tok;
	char			**args;
	char			**files;
	int				*tokens;
	struct s_tokens	*next;
}	t_tokens;

// typedef struct s_tree
// {
// 	struct s_tree *para;
// 	struct s_tree *pipes;
// 	struct s_tree *next;
// }	t_tree;

// void	function(t_tree *node)
// {
// 	if (node->para != NULL)
// 		function(node.para);
// 	if (node->pipes != NULL)
// 		function(node.pipes);
// 	if (node->next != NULL)
// 		function(node.next);
// 	to_child(node);
// }

enum	e_log_op
{
	OPP_AND = 1,
	OPP_OR,
	OPP_PIPE
};

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
	SPLIT_OR,
	FLAGS
};

#endif