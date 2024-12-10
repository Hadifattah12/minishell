/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:32:37 by hfattah           #+#    #+#             */
/*   Updated: 2024/12/10 13:44:13 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_strdupp(char *s);
size_t	ft_strlenn(char *s);
char	*ft_substrr(char *s, unsigned int start, size_t len);
char	*ft_strjoinn(char *s1, char *s2);
void	fill_str(char *res, char *s1, char *s2);

#endif