/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:57:55 by jbax          #+#    #+#                 */
/*   Updated: 2023/02/22 17:10:54 by jbax          ########   odam.nl         */
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
# include "structures.h"
# include "builtins_data_struct.h"
# define _POSIX_SOURCE
# include <sys/wait.h>
# include <sys/types.h>

/* NOT OURS BUT MUST BE DECLARED*/
void		rl_clear_history(void);
void		rl_replace_line(const char *text, int clear_undo);
/* DEFINE'S */
# define EMPTY 1
# define FULL 0
/* OUR FUNCTIONS*/
/**
 * @brief jordan 
 * Set the signal parent object
 * set the use of ctr + c to read from newline
 */
void		set_signal_parrent(void);
/**
 * @brief jordan
 * sets the signals to do nothing
 */
void		block_signal(void);
void		reset_signal(void);
/**
 * @brief jordan
 * use the readline and handels eof and history
 * @return char* line read
 */
char		*read_the_line(void);
/* builtins */
int			what_cmd(char *line, t_super *super);
void		ft_export(t_super *super, char **args, int output_fd);
void		ft_unset(t_super *super, char **arg, int output_fd);
void		ft_exit_builtin(char **arg, t_super *super);
void		ft_pwd(t_super *super, int output_fd);
void		ft_change_dir(char *path);
void		ft_echo(char **arg, int output_fd);
void		ft_put_env(t_super *super, int fd);
void		ft_othercmd(char **arg, t_super *super, int ispipe, int fd);

t_tokens	*tokanize(char *input);
int			print_all_tokens(t_tokens *list);
int			tokanize_main(char *input, t_tokens *list);
t_tokens	*init_list(void);
t_tokens	*new_node(char *input, t_tokens *prev);

char		**copy_env(char **env);
/* splits the string in a malloc'ed copy of the content 
of the env string */
char		*ft_env_content(char *env);
/* splits the string in a malloc'ed copy of the variable name 
of the env string */
char		*ft_env_name(char *env);
/* gives the env array index of the exact match of var names 
-1 if there isn't */
int			ft_env_index(char **env, char *var);
char		*singlearg(char *arg, int *index);
/* poiter is char after $.
returns (malloct) content of var in string of pointer, 
pointer points to the first char of the var
retuns empty string if var has no content but is still malloct
returns 0 if no match can be found. */
char		*ft_getvar(char *ptr, char **env);
char		*ft_replacevar(char *head, int index, char **env);
#endif