#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalnum(int x);
int					ft_isalpha(int x);
int					ft_isascii(int x);
int					ft_isdigit(int x);
int					ft_isprint(int x);
int					ft_toupper(int x);
int					ft_tolower(int x);
int					ft_isspace(int c);

int					ft_atoi(const char *str);
int					ft_strncmp(char *dest, char *src, size_t len);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

char				*ft_itoa(int nbr);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
char				**ft_split(char const *s, char c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

size_t				ft_strlen(const char *a);
size_t				ft_strlcpy(char *dest, char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);

void				ft_bzero(void *s, size_t n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				*ft_calloc(size_t c, size_t s);
void				*ft_memset(void *dest, int c, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *a, const void *b, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

int					ft_lstsize(t_list *lst);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
#endif
