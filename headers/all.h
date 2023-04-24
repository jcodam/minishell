/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:57:55 by jbax          #+#    #+#                 */
/*   Updated: 2023/04/24 17:18:19 by jbax          ########   odam.nl         */
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
# include "../libft/libft.h"
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
/* 1 Global */
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
int			what_cmd(t_tokens *bigdata, t_super *super);
void		ft_export(t_super *super, char **args, int output_fd);
void		ft_unset(t_super *super, char **arg);
void		ft_exit_builtin(char **arg);
void		ft_pwd(int output_fd);
int			ft_change_dir(char **args, t_super *super);
void		ft_echo(char **arg, int output_fd);
void		ft_put_env(t_super *super, int fd);
void		ft_othercmd(char **arg, t_super *super, int ispipe, int fd);

int			print_all_tokens(t_tokens *list);
int			tokanize_main(char *input, t_tokens *list);
t_tokens	*init_list(void);
//t_tokens	*new_node(char *input);

char		**copy_env(char **env);
char		**split_quote(char const *s, char c);
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
/* pointer is char after $.
returns (malloct) content of var in string of pointer, 
pointer points to the first char of the var
retuns empty string if var has no content but is still malloct
returns 0 if no match can be found. */
char		*ft_getvar(char *ptr, char **env);
char		*ft_replacevar(char *head, int index, char **env);
/*returns a list of matching files/dir */
t_list		*get_wildcard(char *wild);
void		exit_errbug(char *error, char *debug);
int			tmpfileswitch(char **line);
int			is_empty(char *line);
/*is_file treu >= 1*/
char		**arr_expander(char **arr, char **env, int is_file);
/* eoh wil be freed and is expected to only have the rellevand data
so use substring
eoh = end of heredoc (the string that ends the heredoc)
tmpfindex wil start trying to creat a temp file 
that ends with that number, use 1 for normal behavior
retuns malloced pointer of the tmp file name */
char		*heredoc(char *eoh, int tmpfindex);
/* set a fd in append mode 0 if error*/
int			setfd_append(char *filename);
/* set a fd in write mode 0 if error*/
int			setfd_write(char *filename);
/* sets a fd in read mode 0 if error*/
int			setfd_read(char *filename);

// @alex functions 
t_tokens	*main_loop(char *input);
int			*make_arr(int len);
void		print_array(int *arr);
int			*tokanize(char *input, int *arr);
int			*label_quotes(char *input, int *arr, int data);
int			*label_vals(int start, int end, int *arr, int sig);
int			*check_operators(char *input, int *arr);
int			*command_after_pipe(char *input, int *arr);
int			*label_spaces(char *input, int *arr);
int			*check_commands(char *input, int *arr);
void		add_node(int start, int *arr, char *input, t_tokens *top);
t_tokens	*split_into_list(char *input, int *arr, t_tokens *list);
void		ms_lstadd_back(t_tokens **lst, t_tokens *new);
void		fill_node(t_tokens *top, char *input, int start, int end);
int			get_node_length(int *arr, int start);
t_tokens	*get_node(int start, int *arr, char *input, t_tokens *tmp);
t_tokens	*lst_end(t_tokens *top);
int			get_index(t_tokens *top);
t_tokens	*setup_new_node(t_tokens *top);
char		get_quote_type(int type);
void		*ms_calloc(size_t nmemb, size_t size);
t_arglist	*add_node_args(t_arglist *args, t_tokens *source);
t_arglist	*convert_list(t_tokens *source);
int			*make_red_op(char *input, int *arr, int i);
int			*make_red_ip(char *input, int *arr, int i);
int			pipe_checker(char *input, int i);
int			red_op_checker(char *input, int i);
int			red_ip_checker(char *input, int i);
void		mini_tokenizer(t_tokens *node);
void		fuzer(t_tokens *list);
void		split_args(t_tokens *list);
//t_tokens	*split_on_pipes(char *input, int *arr, t_tokens *top);
int			amp_checker(char *input, int i);
int			check_OR(char *input, int *arr, int i);
int			check_ampersand(char *input, int *arr, int i);
int			OR_error_checker(char *input, int i);
int			check_pipes(char *input, int *arr, int i);
int			check_l_arrow(char *input, int *arr, int i);
int			check_r_arrow(char *input, int *arr, int i);
/**
 * splits the content of a node at the position given as 'split_points' and 
 * places the righthand part of the string in a new node in the linked list. 
 * noc determines the amount of characters to be splitted on 
 * (i.e. for '&&' noc would be 2)
 * if node_nr is given, it determines the node in which the string 
 * should be split
 */
void		split_to_node(t_tokens *node, int split_point, int noc);
t_tokens	*primary_split(char *input, int *arr, t_tokens *list);
int			*ft_subarr(int *arr, size_t start, size_t len);
int			ar_len(int *arr);
void		fill_node_split(t_tokens	*node, int split_point, int noc);
/**
 * finds the first instance of a specified token in the array. 
 * returns -1 if there is no instance of the token
 */
int			find_tokens(int val, t_tokens *list);
t_tokens	*split_on_amps(t_tokens *list);
int			find_tokens(int val, t_tokens *list);
void		print_tokens(int *arr);
t_tokens	*split_on_or(t_tokens *list);
t_tokens	*split_on_pipes(t_tokens *list);
void		trim_spaces(t_tokens *list);
t_tokens	*find_files(t_tokens *list);
t_tokens	*find_args(t_tokens *list);
int			cut_to_files(t_tokens *list, int i, int val);
int			cut_to_args(t_tokens *list, int i, int val);
void		add_in_node_file(t_tokens *list, int length, int i);
void		add_in_node_arg(t_tokens *list, int length, int i);
int			*calloc_array(int len, int type);
int			*ms_arrdup(int *arr, int len);
void		free_list(t_tokens *list);
void		transpose_file(t_tokens *list, int length, int start, int val);
void		transpose_arg(t_tokens *list, int length, int start);
t_tokens	*check_for_commands(t_tokens *list);
char		**arg_splitter(char **args, int i, int start, int end);
int			count_args(char **args);
void		split_on_flags(t_tokens *list);
char		*mini_space_trimmer(char *string);
void		update_mini_tok(t_tokens *list, int i, int val);
void		split_between_flags(t_tokens *list, int i);
void		free_arr_null(char ***ptr);
void		free_str_null(char **ptr);
//int 		find_tokens(int *arr, int token);
void		attach_token(t_tokens *list, int i);

#endif