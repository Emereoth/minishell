/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 11:00:42 by acottier          #+#    #+#             */
/*   Updated: 2016/09/01 17:56:35 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stddef.h>
# include <stdlib.h>
# include <dirent.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void		*b, int		c, size_t	len);
void				*ft_bzero(void		*s, size_t	n);
void				*ft_memcpy(void		*dst, const void	*src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int	c, size_t	n);
void				*ft_memmove(void *dst, const void *src, size_t	len);
void				*ft_memchr(const void	*s, int			c, size_t		n);
int					ft_memcmp(const void	*s1, const void		*s2, size_t n);
size_t				ft_strlen(const char	*str);
int					ft_tabsize(char **tab);
char				*ft_strdup(const char	*s1);
char				*ft_strndup(const char	*s1, size_t n);
char				*ft_strrmv(char	*str, char	c);
char				*ft_strcpy(char			*dst, char			*src);
char				*ft_strncpy(char	*dst, char		*src, size_t	n);
char				*ft_strcat(char			*s1, char			*s2);
char				*ft_strncat(char		*s1, char			*s2, int	n);
size_t				ft_strlcat(char		*dst, const char	*src, size_t size);
char				*ft_strchr(const char			*s, int			c);
char				*ft_strrchr(const char		*s, int			c);
char				*ft_strstr(char			*s1, char			*s2);
char				*ft_strnstr(char		*s1, char			*s2, int	n);
int					ft_strcmp(char			*s1, char			*s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char	*str);
int					ft_isalpha(int	c);
int					ft_isdigit(int	c);
int					ft_isalnum(int	c);
int					ft_isascii(int	c);
int					ft_isprint(int	c);
int					ft_toupper(int	c);
int					ft_tolower(int	c);
int					ft_factorial(int x);

void				*ft_memalloc(size_t			size);
void				ft_memdel(void				**ap);
char				*ft_strnew(size_t			size);
void				ft_strdel(char				**as);
void				ft_strclr(char				*s);
void				ft_striter(char		*s, void		(*f)(char	*));
void				ft_striteri(char *s, void	(*f)(unsigned int, char	*));
char				*ft_strmap(char const		*s, char	(*f)(char));
char				*ft_strmapi(char const	*s, char (*f)(unsigned int, char));
int					ft_strequ(char const		*s1, char const		*s2);
int					ft_strnequ(char const	*s1, char const		*s2, size_t	n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const		*s2);
char				*ft_strtrim(char const		*s);
char				**ft_strsplit(char const	*s, char			c);
char				*ft_itoa(int				n);
void				ft_putchar(char				c);
void				ft_putstr(char	const		*c);
void				ft_putendl(char	const		*c);
void				ft_putnbr(int				c);
void				ft_putchar_fd(char			c, int	fd);
void				ft_putstr_fd(char	const	*c, int	fd);
void				ft_putendl_fd(char	const	*c, int	fd);
void				ft_putendl_err(char *str);
void				ft_putnbr_fd(int			c, int	fd);
void				ft_puttab(char	**tab);
void				ft_doublestr(char	*str, char	*str2);
void				ft_triplestr(char *str1, char *str2, char *str3);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

void				ft_freetab(char		**tab);
int					ft_sqrt(int n);
int					ft_power(int base, int power);
char				*ft_reverse(char *str);
size_t				ft_strlenchr(char *str, char c);
char				*ft_strdupchr(const char *s1, char c);
char				**ft_newtab(int size);
void				ft_putstr_err(char *str);
char				*ft_trijoin(char	*s1, char	*s2, char	*s3);
char				*ft_addspace(char	*str, int nbr);
int					ft_nbrlength(int	nbr);
char				*ft_stradv(char *str, int i);
int					ft_smallest(int a, int b);
void				ft_clearnstr(char *str, int n);
char				**ft_tabdup(char **tab);
void				ft_capitalize(char *str);

#endif
