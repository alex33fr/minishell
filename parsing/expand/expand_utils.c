/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:18:41 by byonis            #+#    #+#             */
/*   Updated: 2026/05/13 11:09:30 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*append(char *res, char *to_add)
{
	char	*tmp;

	tmp = ft_strjoin(res, to_add);
	free(res);
	return (tmp);
}

static char	*get_env_value(char *name, char **envp, int last_status)
{
	char	*res;
	int		i;
	size_t	len;

	if (ft_strncmp(name, "?", 1) == 0)
	{
		res = ft_itoa(last_status);
		return (res);
	}
	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			res = ft_strdup(&envp[i][len + 1]);
			return (res);
		}
		i++;
	}
	res = ft_strdup("");
	return (res);
}

static int	get_var_len(char *str, int i)
{
	int	var_len;

	if (str[i + 1] == '?')
		return (1);
	var_len = 0;
	while (ft_isalnum(str[i + 1 + var_len]) || str[i + 1 + var_len] == '_')
		var_len++;
	return (var_len);
}

static char	*resolve_var(char *str, int *i, t_expand *ex, int var_len)
{
	char	*var_name;
	char	*value;

	var_name = ft_substr(str, *i + 1, var_len);
	if (!var_name)
		return (NULL);
	value = get_env_value(var_name, ex->envp, ex->last_status);
	free(var_name);
	return (value);
}

char	*handle_dollar(char *str, int *i, t_expand *ex, char *res)
{
	char	*value;
	int		var_len;

	var_len = get_var_len(str, *i);
	if (var_len == 0)
	{
		(*i)++;
		res = append(res, "$");
		return (res);
	}
	value = resolve_var(str, i, ex, var_len);
	if (!value)
		return (NULL);
	res = append(res, value);
	free(value);
	*i += 1 + var_len;
	return (res);
}
