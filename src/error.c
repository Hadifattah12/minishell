
#include "../inc/minishell.h"

extern int	g_status;

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
	else if (err_type == PIPERR)
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

int	check_overflow(long *nbr, int sign, char digit)
{
	int limit_digit;

	if (sign == 1)
		limit_digit = LONG_MAX % 10;
	else
		limit_digit = LONG_MAX % 10 + 1;

	if (*nbr > LONG_MAX / 10 || (*nbr == LONG_MAX / 10 && (digit - '0') > limit_digit))
	{
		if (sign == 1)
			*nbr = LONG_MAX;
		else
			*nbr = LONG_MIN;
		return (-1);
	}
	return (0);
}


int	ft_atoi2(const char *nptr, long *nbr)
{
	int	sign;

	*nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	if (!ft_isdigit(*nptr))
		return (-1);
	while (ft_isdigit(*nptr))
	{
		if (check_overflow(nbr, sign, *nptr) == -1)
			return (-1);
		*nbr = 10 * *nbr + (*nptr++ - '0');
	}
	if (*nptr && !ft_isspace(*nptr))
		return (-1);
	*nbr *= sign;
	return (0);
}

int mini_exit(t_list *cmd, int *is_exit)
{
    t_mini  *node;
    long    status[2];

    node = cmd->content;
    *is_exit = !cmd->next;
    if (*is_exit)
        ft_putstr_fd("exit\n", 2);
    if (!node->full_cmd || !node->full_cmd[1])
        return g_status;
    status[1] = ft_atoi2(node->full_cmd[1], &status[0]);
    if (status[1] == -1)
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(node->full_cmd[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        return (255);
    }
    else if (node->full_cmd[2])
    {
        *is_exit = 0;
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return (1);  
    }
    status[0] = (unsigned char)(status[0] % 256);
    return (status[0]);
}

void	cd_error(char **str[2])
{
	DIR		*dir;

	dir = NULL;
	if(str[0][1] && str[0][2])
	{
		g_status = 1;
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
	if (str[0][1])
		dir = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
	{
		g_status = 1;
		ft_putstr_fd("minishell: HOME not set\n", 2);
	}
	if (str[1][0] && !str[0][1])
		g_status = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		mini_perror(NDIR, str[0][1], 1);
	else if (str[0][1])
		mini_perror(NOT_DIR, str[0][1], 1);
	if (str[0][1] && dir)
		closedir(dir);
}

void	free_content(void *content)
{
	t_mini	*node;

	node = content;
	ft_free_matrix(&node->full_cmd);
	free(node->full_path);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	free(node);
}