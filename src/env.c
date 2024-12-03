/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:54:00 by hfattah           #+#    #+#             */
/*   Updated: 2024/12/03 16:44:52 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*mini_getenv(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

char	**mini_setenv(char *var, char *value, char **envp, int n)
{
	int		i[2];
	char	*aux[2];

	if (n < 0)
		n = ft_strlen(var);
	i[0] = -1;
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_i(envp[i[0]], '='))
			i[1] = ft_strchr_i(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			aux[0] = envp[i[0]];
			envp[i[0]] = aux[1];
			free(aux[0]);
			return (envp);
		}
	}
	envp = ft_extend_matrix(envp, aux[1]);
	free(aux[1]);
	return (envp);
}

static int	var_in_envp(char *argv, char **envp, int ij[2])
{
	int	pos;

	ij[1] = 0;
	pos = ft_strchr_i(argv, '=');
	if (pos == -1)
		return (-1);
	while (envp[ij[1]])
	{
		if (!ft_strncmp(envp[ij[1]], argv, pos + 1))
		{
			free(envp[ij[1]]);
			return (1);
		}
		ij[1]++;
	}
	return (0);
}
int env_cmp(const void *a, const void *b) {
    const char *env_a = *(const char **)a;
    const char *env_b = *(const char **)b;

    // Compare the environment variable names (before the '=' character)
    while (*env_a && *env_b && *env_a == *env_b) {
        env_a++;
        env_b++;
    }

    // Custom sorting: Uppercase letters come before lowercase
    if (toupper((unsigned char)*env_a) == toupper((unsigned char)*env_b)) {
        return *env_a - *env_b;  // If characters are same, compare their ASCII value
    }
    return toupper((unsigned char)*env_a) - toupper((unsigned char)*env_b);  // Case-insensitive comparison
}

// Function to sort and export environment variables
void sort_env(char **env) {
    int i = 0;

    // Count the number of environment variables
    while (env[i] != NULL) {
        i++;
    }

    // Sort the environment variables using qsort
    qsort(env, i, sizeof(char *), env_cmp);

    // Print the sorted environment variables and simulate export
    for (int j = 0; j < i; j++) {
        write(1, "declare -x ", 11);           // Simulate export command
        write(1, env[j], strlen(env[j]));  // Print the environment variable
        write(1, "\n", 1);              // Newline after each export
    }
}

// Handle export command
void handle_export(t_prompt *prompt) {
    // Sort the environment variables passed through prompt->envp
    sort_env(prompt->envp);
}

int	mini_export(t_prompt *prompt)
{
	int		ij[2];
	int		pos;
	char	**argv;

	argv = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(argv) == 1)
		handle_export(prompt);
	if (ft_matrixlen(argv) >= 2)
	{
		ij[0] = 1;
		while (argv[ij[0]])
		{
			pos = var_in_envp(argv[ij[0]], prompt->envp, ij);
			if (pos == 1)
				prompt->envp[ij[1]] = ft_strdup(argv[ij[0]]);
			else if (ft_strchars_i(argv[ij[0]], "~{}-#!+@.") >= 0)
			{
				printf("minishell: '%s'not a valid identifier\n", argv[ij[0]]);
				return (1);
			}
			else if (!pos)
				prompt->envp = ft_extend_matrix(prompt->envp, argv[ij[0]]);
			ij[0]++;
		}
	}
	return (0);
}

int	mini_unset(t_prompt *prompt)
{
	char	**argv;
	char	*aux;
	int		ij[2];

	ij[0] = 0;
	argv = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(argv) >= 2)
	{
		while (argv[++ij[0]])
		{
			if (argv[ij[0]][ft_strlen(argv[ij[0]]) - 1] == '=')
				return (0);
			aux = ft_strjoin(argv[ij[0]], "=");
			free(argv[ij[0]]);
			argv[ij[0]] = aux;
			if (var_in_envp(argv[ij[0]], prompt->envp, ij))
				ft_matrix_replace_in(&prompt->envp, NULL, ij[1]);
		}
	}
	return (0);
}
