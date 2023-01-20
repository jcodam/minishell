/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 17:16:08 by jbax          #+#    #+#                 */
/*   Updated: 2023/01/20 17:27:27 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* mem functions */
/** The memset() function writes len bytes
 *  of value c (converted to an unsigned char) to the string b.*/
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dest, const void *stc, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
/* takes 2 pointer and compers them for n bytes
retuns the difrents between the first difrent byte in the array
by s1 - s2 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);

/** change a char to lowercase */
int		ft_tolower(int c);
/* change a char to uppercase */
int		ft_toupper(int c);

/* finds char c in string s
returns pionter of the first match in s if found
returns NULL if not found */
char	*ft_strchr(const char *s, int c);
/* finds char c in string s
returns pionter of the last match in s if found
returns NULL if not found */
char	*ft_strrchr(const char *s, int c);
/* give's the size of a string */
size_t	ft_strlen(const char *s);
/* finds de second string in the first and returns 
a pointer of the begining of the second string in the first 
NULL if it isn't there */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
/* changes a sting to NULL for N bytes */
void	ft_bzero(void *s, size_t n);
/* takes 2 strings and compers them for n bytes
retuns the difrents between the first difrent char in the strings
by s1 - s2 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/* makes a malloc allocated copy of a string */
char	*ft_strdup(const char *s);
/* strlcpy() copies up to dstsize - 1 characters 
from the string src to dst,
NUL-terminating the result if dstsize is not 0. */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
/* strlcat() appends string src to the end of dst.
It will append at most dstsize - strlen(dst) - 1 characters.
It will then NUL-terminate, unless dstsize is 0 or
the original dst string was longer than dstsize 
(in practice this should not happen). */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/* changes a srting to a int 
if no numbers in string retuns 0
if number cant fit in a int returns -1 */
int		ft_atoi(const char *nptr);

/* allocates (with malloc) memory of nmemb units times
the size of each unit */
void	*ft_calloc(size_t nmemb, size_t size);

/* checks if a character is in the alfabet
returns 1 for lowercase
returns 2 for uppercase
returns 0 if not true */
int		ft_isalpha(int c);
/* checks if a character is in the alfabet
returns 1 for lowercase
returns 2 for uppercase
returns 3 for number
returns 0 if not true */
int		ft_isalnum(int c);
/* checks if a character is a number
returns 3 for number
returns 0 if not true */
int		ft_isdigit(int c);
/* checks if a character is a ascii value
returns 11 for ascii value
returns 0 if not true */
int		ft_isascii(int c);
/* checks if a character is can be seen if printed
returns 12 for true
returns 0 if not true */
int		ft_isprint(int c);

/* Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len */
char	*ft_substr(char const *s, unsigned int start, size_t len);
/* Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string. */
char	*ft_strtrim(char const *s1, char const *set);
/* Applies the function ’f’ to each character of the
string ’s’, and passing its index as first argument
to create a new string (with malloc(3)) resulting
from successive applications of ’f’. */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/* Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’ */
char	*ft_strjoin(char const *s1, char const *s2);
/* Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary. */
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
/* Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled. */
char	*ft_itoa(int n);
/* Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer. */
char	**ft_split(char const *s, char c);

/* Outputs the character ’c’ to the given file
descriptor. */
void	ft_putchar_fd(char c, int fd);
/* Outputs the string ’s’ to the given file
descriptor. */
void	ft_putstr_fd(char *s, int fd);
/* Outputs the string ’s’ to the given file descriptor
followed by a newline. */
void	ft_putendl_fd(char *s, int fd);
/* Outputs the integer ’n’ to the given file
descriptor */
void	ft_putnbr_fd(int n, int fd);

/* Adds the node ’new’ at the beginning of the list. */
void	ft_lstadd_front(t_list **lst, t_list *new);
/* Adds the node ’new’ at the end of the list. */
void	ft_lstadd_back(t_list **lst, t_list *new);
/* Allocates (with malloc(3)) and returns a new node t_list.
The member variable ’content’ is initialized with
the value of the parameter ’content’. The variable
’next’ is initialized to NULL. */
t_list	*ft_lstnew(void *content);
/* Counts the number of nodes in a list. */
int		ft_lstsize(t_list *lst);
/* Returns the last node of the list. */
t_list	*ft_lstlast(t_list *lst);
/* Takes as a parameter a node and frees the memory of
the node’s content using the function ’del’ given
as a parameter and free the node. The memory of
’next’ must not be freed. */
void	ft_lstdelone(t_list *lst, void (*del)(void*));
/* Deletes and frees the given node and every
successor of that node, using the function ’del’
and free(3).
Finally, the pointer to the list must be set to
NULL. */
void	ft_lstclear(t_list **lst, void (*del)(void*));
/* Iterates the list ’lst’ and applies the function
’f’ on the content of each node. */
void	ft_lstiter(t_list *lst, void (*f)(void *));
/* Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
