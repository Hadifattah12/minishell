
#include "../inc/libft.h"

t_list	*ft_matrixtolst(char **matrix)
{
	t_list	*lst;
	int		i;

	lst = NULL;
	i = -1;
	while (matrix[++i])
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(matrix[i])));
	return (lst);
}
