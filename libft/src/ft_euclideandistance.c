
#include "../inc/libft.h"

int	ft_euclideandistance(t_vector src, t_vector dest)
{
	return (ft_sqrt(ft_recursive_power(dest.x - src.x, 2) + \
							ft_recursive_power(dest.y - src.y, 2)));
}
