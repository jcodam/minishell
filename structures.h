/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structures.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 18:03:40 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/01/22 16:57:08 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "all.h"

typedef struct s_tokens
{
	int				type;
	int				priority;
	int				start;
	int				end;
	char			*content;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}	t_tokens;

enum e_commands
{
	QUOTE_SL,
	QUOTE_DL,
	REDIRECT_IP,
	REDIRECT_OP,
	RD_TIL_DELIM,
	REDIRECT_APPEND,
	PIPE,
	ENV_VAR,
	MS_ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	OTHER
};

#endif