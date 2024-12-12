/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:24:52 by hfattah           #+#    #+#             */
/*   Updated: 2024/12/12 09:55:02 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

static char	*ft_strchrr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

static char	*_set_line(char *line)
{
	char	*left_c;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[1] == 0)
		return (NULL);
	left_c = ft_substrr(line, i + 1, ft_strlenn(line) - i);
	if (*left_c == 0)
	{
		free(left_c);
		left_c = NULL;
	}
	line[i + 1] = 0;
	return (left_c);
}

static char	*update_stock(int fd, char *left_c, char *stock)
{
	ssize_t	readcheck;
	char	*tmp;

	readcheck = 1;
	while (readcheck > 0)
	{
		readcheck = read(fd, stock, BUFFER_SIZE);
		if (readcheck == -1)
		{
			free(left_c);
			return (NULL);
		}
		else if (readcheck == 0)
			break ;
		stock[readcheck] = 0;
		if (!left_c)
			left_c = ft_strdupp("");
		tmp = left_c;
		left_c = ft_strjoinn(tmp, stock);
		free(tmp);
		tmp = NULL;
		if (ft_strchrr(stock, '\n'))
			break ;
	}
	return (left_c);
}

char	*get_next_line(int fd)
{
	static char	*left_c;
	char		*line;
	char		*stock;

	stock = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(left_c);
		free(stock);
		left_c = NULL;
		stock = NULL;
		return (NULL);
	}
	if (!stock)
		return (NULL);
	line = update_stock(fd, left_c, stock);
	free(stock);
	stock = NULL;
	if (!line)
		return (NULL);
	left_c = _set_line(line);
	return (line);
}
