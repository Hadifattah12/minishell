/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:10:33 by hfattah           #+#    #+#             */
/*   Updated: 2024/12/05 15:00:37 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_export(char *argv, t_prompt *prompt)
{
	int		i;
	char	**export;

	export = prompt->export;
	i = -1;
	while (export[++i])
	{
		if (!ft_strncmp(argv, export[i], ft_strlen(argv)))
		{
			return ;
		}	
	}
	prompt->export = ft_extend_matrix(prompt->export, argv);
}
