/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:57:55 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/17 16:19:31 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H
/* INCLUDES */
# include <termios.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include "libft/libft.h"	
/* NOT OURS BUT MUST BE DECLARED*/
void	rl_clear_history(void);
void	rl_replace_line(const char *text, int clear_undo);
/* DEFINE'S */
# define EMPTY 1
# define FULL 0
/* OUR FUNCTIONS*/
void	set_signal_parrent(void);
void	block_signal(void);
char	*read_the_line(void);

#endif