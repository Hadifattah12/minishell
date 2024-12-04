/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:18:54 by hfattah           #+#    #+#             */
/*   Updated: 2024/12/03 14:56:33 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	*check_to_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_mini	*n;
	DIR		*dir;

	n = cmd->content;
	dir = NULL;
	if (n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (n->infile == -1 || n->outfile == -1)
		return (NULL);
	if ((n->full_path && access(n->full_path, X_OK) == 0) || is_builtin(n))
		exec_fork(prompt, cmd, fd);
	else if (!is_builtin(n) && ((n->full_path && \
	!access(n->full_path, F_OK)) || dir))
		g_status = 126;
	else if (!is_builtin(n) && n->full_cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}

void	*mini_perror_helper(int err_type, char *param)
{
	if (err_type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err_type == PIPENDERR)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (err_type == MEM)
		ft_putstr_fd("minishell: no memory left on device\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	else if (err_type == 15)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}

void	*mini_perror(int err_type, char *param, int err)
{
	g_status = err;
	if (err_type == QUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote\n", 2);
	else if (err_type == NDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("minishell: fork failed\n", 2);
	mini_perror_helper(err_type, param);
	return (NULL);
}


int	var_in_envp_unset(char *argv, char **envp, int ij[2])
{
	int	pos;

	ij[1] = 0;
	pos = ft_strchr_i(argv, '=');
	if (pos == -1)
		return (-1);
	while (envp[ij[1]])
	{
		if (!ft_strncmp(envp[ij[1]], argv, pos + 1))
			return (1);
		ij[1]++;
	}
	return (0);
}