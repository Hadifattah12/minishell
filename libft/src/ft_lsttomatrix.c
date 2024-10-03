
#include "../inc/libft.h"

char	**ft_lsttomatrix(t_list *lst)
{
	char	**matrix;
	t_list	*aux;
	char	*temp;

	aux = lst;
	matrix = NULL;
	while (aux)
	{
		temp = ft_strdup(aux->content);
		matrix = ft_extend_matrix(matrix, temp);
		aux = aux->next;
		free(temp);
	}
	return (matrix);
}
