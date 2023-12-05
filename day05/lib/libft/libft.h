/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:11:23 by jcodina-          #+#    #+#             */
/*   Updated: 2023/11/11 19:28:15 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifdef __linux__
#  include <stdint.h>
#  include <stddef.h>
# elif _WIN32
#  include <stdint.h>
#  include <io.h>
# elif defined(__APPLE__)
#  define ON_APPLE 1
#  include <unistd.h>
# endif
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# define LOWER_HEX 0
# define UPPER_HEX 1
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef enum
{
	true = 1,
	false = 0
}	en_bool;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//Allocating space

void	*ft_calloc(size_t count, size_t size);

//Arithmetic Functions

int		ft_atoi(const char *nptr);
char	*ft_itoa(const int n);
char	*ft_uitoa(const unsigned int n);

//Character Handling

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

//Input & Output on Streams

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(long nb, int fd);
int		ft_putnbrlen_fd(long nb, int fd);
void	ft_putnbr_base(long long nbr, char *base);
int		ft_putnbrlen_base(long long nbr, char *base);
int		ft_putnbrlen_hex(long long nbr, int hex_type);
void	ft_putstr_fd(char *s, int fd);
int		ft_putstrlen_fd(char *s, int fd);
char	*get_next_line(int fd);

//Search Functions

void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char **s1, char **s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//String and Array Comparison

int		ft_memcmp(const void *s1, const void *s2, size_t n);

//String and Array Copying & Concatenating

void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);

//String and Array Utilities

size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

//List manipulation

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

#endif
