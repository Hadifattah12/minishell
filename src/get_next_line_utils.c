/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:54:32 by hfattah           #+#    #+#             */
/*   Updated: 2024/12/12 09:54:15 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

char	*ft_strdupp(char *s1)
{
	char			*dest;
	unsigned int	i;

	dest = (char *) malloc(ft_strlenn(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

size_t	ft_strlenn(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substrr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlenn(s))
		return (malloc(1));
	if (len > ft_strlenn(s + start))
		len = ft_strlenn(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strjoinn(char *s1, char *s2)
{
	char			*res;

	res = (char *) malloc((ft_strlenn(s1) + ft_strlenn(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	fill_str(res, s1, s2);
	return (res);
}

void	fill_str(char *res, char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
}
