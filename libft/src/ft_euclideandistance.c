/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_euclideandistance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:20:57 by hfattah           #+#    #+#             */
/*   Updated: 2024/12/03 13:20:58 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_euclideandistance(t_vector src, t_vector dest)
{
	return (ft_sqrt(ft_recursive_power(dest.x - src.x, 2) + \
							ft_recursive_power(dest.y - src.y, 2)));
}
