#include "../../includes/minishell.h"
#include <stdlib.h>

t_malloc	*get_garbage_c(void)
{
	static t_malloc	garbage_c = {NULL, NULL};

	return (&garbage_c);
}

void	*gc_malloc(unsigned int size)
{
	void		*ptr;
	t_malloc	*garbage_c;

	garbage_c = get_garbage_c();
	while (garbage_c->next)
		garbage_c = garbage_c->next;
	garbage_c->next = ft_calloc(1, sizeof(t_malloc));
	if (!garbage_c->next)
		exit(1);
	ptr = ft_calloc(1, size);
	if (!ptr)
		exit(1);
	garbage_c->next->ptr = ptr;
	return (ptr);
}

void	add_garbage_c(void *ptr)
{
	t_malloc	*garbage_c;

	if (!ptr)
		exit(1);
	garbage_c = get_garbage_c();
	while (garbage_c->next)
		garbage_c = garbage_c->next;
	garbage_c->next = ft_calloc(1, sizeof(t_malloc));
	if (!garbage_c->next)
	{
		free(ptr);
		exit(1);
	}
	garbage_c->next->ptr = ptr;
}
