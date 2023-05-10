/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 15:02:16 by jbax          #+#    #+#                 */
/*   Updated: 2023/05/10 15:10:37 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/builtins_data_struct.h"
#include <termios.h>
#include <unistd.h>

void	set_term(struct termios *term, int option)
{
	tcsetattr(STDIN_FILENO, option, term);
	tcsetattr(STDOUT_FILENO, option, term);
	tcsetattr(STDERR_FILENO, option, term);
}
