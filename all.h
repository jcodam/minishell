/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:57:55 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/02 16:49:53 by jbax          ########   odam.nl         */
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
/* 1 Globle */
int	g_exit_code;
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
void		ft_unset(t_super *super, char **arg);
void		ft_exit_builtin(char **arg);
void		ft_pwd(int output_fd);
void		ft_change_dir(char *path);
void		ft_echo(char **arg, int output_fd);
void		ft_put_env(t_super *super, int fd);
void		ft_othercmd(char **arg, t_super *super, int ispipe, int fd);

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
void		exit_errbug(char *error, char *debug);

t_tokens	*main_loop(char *input);
int			*make_arr(int len);
void		print_array(int *arr);
int			*tokanize(char *input, int *arr);
int			*label_quotes(char *input, int *arr, int data);
int			*label_vals(int start, int end, int *arr, int sig);
int			*check_operators(char *input, int *arr);
int			*command_after_pipe(char *input, int *arr);
int			*trim_spaces(char *input, int *arr);
int			*check_commands(char *input, int *arr);
void		add_node(int start, int *arr, char *input, t_tokens *top);
t_tokens	*split_into_list(char *input, int *arr, t_tokens *list);
void		ms_lstadd_back(t_tokens **lst, t_tokens *new);
void		add_node_end(char *input, t_tokens *top, int type);
void		fill_node(t_tokens *top, char *input, int start, int end);
void		add_node(int start, int *arr, char *input, t_tokens *top);
int			get_node_length(int *arr, int start);
t_tokens	*get_node(int start, int *arr, char *input, t_tokens *tmp);
t_tokens	*lst_end(t_tokens *top);
int			get_index(t_tokens *top);
t_tokens	*setup_new_node(t_tokens *top);
char		get_quote_type(int type);
void		*ms_calloc(size_t nmemb, size_t size);

#endif