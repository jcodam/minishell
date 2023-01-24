/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:57:55 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/24 19:27:36 by jbax          ########   odam.nl         */
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
/**
 * @brief jordan 
 * Set the signal parrent object
 * set the use of ctr + c to read from newline
 */
void	set_signal_parrent(void);
/**
 * @brief jordan
 * sets the signals to do nothing
 */
void	block_signal(void);
/**
 * @brief jordan
 * use the readline and handels eof and history
 * @return char* line read
 */
char	*read_the_line(void);
void	ft_pwd(int output_fd);
int		what_cmd(char *line, char **envp);
void	ft_change_dir(char *path);
void	ft_echo(char *str, int argument, int output_fd);
void	ft_export_no_arguments(char **env, int output_fd);
char	**copy_env(char **env);
/* makes new arr without content in index and frees old pointer. NULL if mem aloc failed */
char	**ft_arrdell_index(char **arr, int index);
/* makes new array with string s in index and frees old pionter. NULL if mem aloc failed */
char	**ft_arradd_index(char **arr, char *s, int index);
/* searches array haystack for string needle and returns the pointer if found. NULL if not found */
char	*ft_arrnstr(char **haystack, char *needle, int *index);
/* prints the char arry in full with newlines in betwine to file descriptor */
void	ft_putarrs_fd(char **arr, int fd);

#endif