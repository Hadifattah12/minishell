/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:26:36 by hfattah           #+#    #+#             */
/*   Updated: 2024/12/10 13:25:24 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	validate_rules(char *str, int i, int quotes[2])
{
	if ((!quotes[0] && !quotes[1] && str[i] == '~')
		&& (i == 0 || (str[i - 1] == ' '))
		&& (str[i + 1] == '\0' || str[i + 1] == ' ' || str[i + 1] == '/'))
		return (1);
	return (0);
}

char	*expand_path(char *str, int i, int quotes[2], char *var)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (validate_rules(str, i, quotes))
		{
			aux = ft_substr(str, 0, i);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (expand_path(str, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (str);
}

char	*get_substr_var(char *str, int i, t_prompt *prompt)
{
	char	*aux;
	int		pos;
	char	*path;
	char	*var;

	pos = ft_strchars_i(&str[i], "|\"\'$?><:{};/% ")
		+ (ft_strchr("$?", str[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(str) - 1;
	aux = ft_substr(str, 0, i - 1);
	var = mini_getenv(&str[i], prompt->envp,
			ft_strchars_i(&str[i], "\"\'$|><:{};/% "));
	if (!var && str[i] == '$')
		var = ft_itoa(prompt->pid);
	else if (!var && str[i] == '?')
		var = ft_itoa(g_status);
	path = ft_strjoin(aux, var);
	free(aux);
	aux = ft_strjoin(path, &str[i + pos]);
	free(var);
	free(path);
	free(str);
	return (aux);
}

// char	*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt)
// {
// 	quotes[0] = 0;
// 	quotes[1] = 0;
// 	while (str && str[++i])
// 	{
// 		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
// 		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
// 		if (!quotes[0] && str[i] == '$' && str[i + 1]
// 			&& ((ft_strchars_i(&str[i + 1], "/~%^{}:;= ") && !quotes[1])
// 				|| (ft_strchars_i(&str[i + 1], "/~%^{}:;=\"") && quotes[1])))
// 			return (expand_vars(get_substr_var(str, ++i, prompt), -1,
// 					quotes, prompt));
// 	}
// 	return (str);
// }

char *ft_strjoin_char(char *str, char c)
{
    size_t len = ft_strlen(str);
    char *result = malloc(len + 2);
    if (!result)
        return NULL;
    ft_strlcpy(result, str, len + 1);
    result[len] = c;
    result[len + 1] = '\0';

    return result;
}

char *handle_variable_expansion(char *result, char *str, int i, t_prompt *prompt)
{
    char *var_name;
    char *var_value;
    char *temp;
    int j;

    j = i + 1;
    while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
        j++;
    var_name = ft_substr(str, i + 1, j - (i + 1));
    var_value = mini_getenv(var_name, prompt->envp, ft_strlen(var_name));
    free(var_name);

    if (!var_value)
        var_value = ft_strdup("");
    temp = result;
    result = ft_strjoin(result, var_value);
    free(temp);
    free(var_value);

    return result;
}

int update_index_after_expansion(char *str, int i)
{
    int j = i + 1;
    while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
        j++;
    return j - 1;
}

char *expand_vars(char *str, int i, int quotes[2], t_prompt *prompt)
{
    char *result;
    char *temp;

    result = ft_strdup("");
    quotes[0] = 0;
    quotes[1] = 0;
    while (str && str[++i])
    {
        quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
        quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;

        if (!quotes[0] && str[i] == '$' && str[i + 1])
        {
            result = handle_variable_expansion(result, str, i, prompt);
            i = update_index_after_expansion(str, i);
        }
        else
        {
            temp = result;
            result = ft_strjoin_char(result, str[i]);
            free(temp);
        }
    }
    free(str);
    return result;
}

int	mini_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}
