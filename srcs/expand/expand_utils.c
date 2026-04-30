/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:18:41 by byonis            #+#    #+#             */
/*   Updated: 2026/04/30 13:44:16 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	find_the_next_valid_variable(char *s, int start, int *in_double_quotes)
{
	int	i;
	// int	in_double_quotes;

	i = start;
	// in_double_quotes = 0;
	while (s && s[i])
	{
		if (s[i] == '"')
			*in_double_quotes = !(*in_double_quotes);
		if (s[i] == '\'' && !(*in_double_quotes))
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (!s[i])
				break ;
		}
		if (s[i] == '$' && s[i + 1]
			&& (ft_isalpha(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
			return (i);
		i++;
	}
	return (-1);
}

char	*var_extraction(char *str, int pos)
{
	int		len;
	char	*res;

	if (!str || pos == -1 || !str[pos + 1])
		return (NULL);
	if (str[pos + 1] == '?')
	{
		res = ft_strdup("?");
		return (res);
	}
	len = 0;
	while (str[pos + len + 1]
		&& (ft_isalnum(str[pos + len + 1]) || str[pos + len + 1] == '_'))
		len++;
	res = ft_substr(str, pos + 1, len);
	return (res);
}

static char	*find_env_value(char *name, char **envp)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

/*
ATTENTION !!!!!!

IL FAUT LAST_STATUS POUR CETTE FONCTION !!!!!
*/

char	*var_replaced(char *str, char **envp, int pos) // rajouter int last_status
{
	char	*temp;
	char	*res;
	char	*val;

	if (!envp || !str)
		return (NULL);
	temp = var_extraction(str, pos);
	if (!temp)
		return (NULL);
	// if (ft_strncmp(temp, "?", 1) == 0)
	// 	res = ft_itoa(last_status);
	// 	if (!res)
	//		return (NULL);
	// else
	// {
	// val = find_env_value(temp, envp);
	// free(temp);
	// if (!val)
	// 	res = ft_strdup("");
	// else
	// 	res = ft_strdup(val);
	// 	}
	val = find_env_value(temp, envp);
	free(temp);
	if (!val)
		res = ft_strdup("");
	else
		res = ft_strdup(val);
	return (res);
}
