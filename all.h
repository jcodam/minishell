/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:57:55 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/29 16:49:19 by jbax          ########   odam.nl         */
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
/**
 * @brief jordan
 * use the readline and handels eof and history
 * @return char* line read
 */
int			what_cmd(char *line, char ***env);
void		ft_export(char ***env, char *arg, int output_fd);

char		*read_the_line(void);
void		ft_pwd(int output_fd);
void		ft_change_dir(char *path);
void		ft_echo(char *str, int argument, int output_fd);
t_tokens	*tokanize(char *input);
int			print_all_tokens(t_tokens *list);
int			tokanize_main(char *input, t_tokens *list);
t_tokens	*init_list(void);
t_tokens	*new_node(char *input, t_tokens *prev);

char		**copy_env(char **env);
void		ft_put_env(char **env, int fd);
/* splits the string in a malloc'ed copy of the content of the env string */
char		*ft_env_content(char *env);
/* splits the string in a malloc'ed copy of the variable name of the env string */
char		*ft_env_name(char *env);
#endif