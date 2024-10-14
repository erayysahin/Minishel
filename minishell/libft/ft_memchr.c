#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		ch;
	unsigned const char	*str;

	ch = c;
	str = (unsigned const char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == ch)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
