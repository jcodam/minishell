#ifndef ALL_H
# define ALL_H
/* INCLUDES */
#include <termios.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
/* NOT OURS BUT MUST BE DECLARED*/
void	rl_clear_history(void);
void	rl_replace_line(const char *, int);
/* DEFINE'S */
#define EMPTY 1
#define FULL 0
/* OUR FUNCTIONS*/
void	set_signal_parrent(void);
char	*read_the_line(void);

#endif