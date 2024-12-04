

#include "../inc/minishell.h"

int env_cmp(const char *env_a, const char *env_b)
{
    while (*env_a && *env_b && *env_a == *env_b)
    {
        env_a++;
        env_b++;
    }

    if (((unsigned char)*env_a) == ((unsigned char)*env_b))
        return *env_a - *env_b;
    return (((unsigned char)*env_a) - ((unsigned char)*env_b));
}

void write_export(char **env, int i)
{
    int j;

    j = 0;
    while (j < i)
    {
        if (ft_strncmp(env[j], "_=", 2) != 0)
        {
            if (ft_strchars_i(env[j], "=") == -1)
            {
                printf("declare -x %s\n", env[j]);
            }
            else
            {
                write(1, "declare -x ", 11);
                write(1, env[j], ft_strchars_i(env[j], "="));
                write(1, "=\"", 2);
                write(1, &env[j][ft_strchars_i(env[j], "=") + 1], ft_strlen(env[j]) - ft_strchars_i(env[j], "="));
                write(1, "\"\n", 2);
            }
        }
        j++;
    }
}

void sort_env(char **env)
{
    int i;
    int j;
    char *temp;
    int pass;

    i = 0;
    pass = 0;
    while (env[i] != NULL)
        i++;
    while (pass < i - 1)
    {
        j = 0;
        while (j < i - pass - 1)
        {
            if (env_cmp(env[j], env[j + 1]) > 0)
            {
                temp = env[j];
                env[j] = env[j + 1];
                env[j + 1] = temp;
            }
            j++;
        }
        pass++;
    }
    write_export(env, i);
}

int mini_export(t_prompt *prompt)
{
    int ij[2];
    int pos;
    char **argv;

    argv = ((t_mini *)prompt->cmds->content)->full_cmd;
    if (!argv[1] && (ft_matrixlen(argv) == 1))
        sort_env(prompt->export);
    if (ft_matrixlen(argv) >= 2)
    {
        ij[0] = 0;
        while (argv[++ij[0]])
        {
            pos = var_in_envp(argv[ij[0]], prompt->envp, ij);
            if (pos == 1)
                prompt->envp[ij[1]] = ft_strdup(argv[ij[0]]);
            else if (pos == -1)
                prompt->export = ft_extend_matrix(prompt->export, argv[ij[0]]);
            else if (ft_strchars_i(argv[ij[0]], "~{}-#!+@.") >= 0 || pos == -2)
                return (print_error_export(prompt, argv[ij[0]]));
            else if (!pos)
                extend_export(prompt, argv[ij[0]]);
        }
    }
    return (0);
}

void handle_unset(char *argv,t_prompt *prompt)
{
    int     i;
    char    **argument;

    i = -1;
    argument = prompt->export;
    while(argument[++i])
    {
        if(!ft_strncmp(argv,argument[i],ft_strlen(argv)))
        {
            ft_matrix_replace_in(&prompt->export, NULL, i);
            return ;
        }
    }
}

int mini_unset(t_prompt *prompt)
{
    char **argv;
    char *aux;
    int ij[2];

    ij[0] = 0;
    argv = ((t_mini *)prompt->cmds->content)->full_cmd;

    if (ft_matrixlen(argv) >= 2)
    {
        while (argv[++ij[0]])
        {
            if(ft_strchars_i(argv[ij[0]],"=") == -1)
                handle_unset(argv[ij[0]],prompt);
            if (argv[ij[0]][ft_strlen(argv[ij[0]]) - 1] == '=')
                return (0);
            aux = ft_strjoin(argv[ij[0]], "=");
            free(argv[ij[0]]);
            argv[ij[0]] = aux;
            if (var_in_envp_unset(argv[ij[0]], prompt->envp, ij))
            {
                ft_matrix_replace_in(&prompt->envp, NULL, ij[1]);
                ft_matrix_replace_in(&prompt->export, NULL, ij[1]);
            }
        }
    }
    return (0);
}