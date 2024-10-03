
#include "../inc/libft.h"

t_list	*ft_lstget_at(t_list *lst, int i)
{
	t_list	*target;
	int		j;

	j = 0;
	if (!lst)
		return (NULL);
	while (lst && j++ < i)
		lst = lst->next;
	target = lst;
	return (target);
}
