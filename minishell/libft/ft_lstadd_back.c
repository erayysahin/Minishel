#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lstlast;

	if (!*lst)
		*lst = new;
	else
	{
		lstlast = ft_lstlast(*lst);
		lstlast->next = new;
	}
}
