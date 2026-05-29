/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:55:13 by byonis            #+#    #+#             */
/*   Updated: 2026/05/29 11:42:38 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static size_t	get_env_len(char *str, int *i, t_expand *ex)
{
	int		var_len;
	char	*value;
	size_t	len;

	var_len = 0;
	if (str[*i + 1] == '?' || str[*i + 1] == '$')
		var_len = 1;
	else
	{
		while (ft_isalnum(str[*i + 1 + var_len])
			|| str[*i + 1 + var_len] == '_')
			var_len++;
	}
	if (var_len == 0)
	{
		(*i)++;
		return (1);
	}
	value = resolve_var(str, i, ex, var_len);
	if (!value)
		return (0);
	len = ft_strlen(value);
	free(value);
	*i += 1 + var_len;
	return (len);
}

static size_t	process_len_char(char *str, int *i, t_expand *ex)
{
	if (manage_dollar_before_quote(str, i, ex)
		|| manage_quotes(str, i, ex))
		return (0) ;
	if (!str[*i] || (str[*i] == '$' && !ex->in_squote))
		return (get_env_len(str, i, ex));
	if (str[*i] == '\\' && !ex->in_dquote && !ex->in_squote)
	{
		(*i)++;
		if (str[*i])
		{
			(*i)++;
			return (1);
		}
		return (0);
	}
	(*i)++;
	return (1);
}

size_t	get_expanded_len(char *str, char **envp, int last_status)
{
	t_expand	ex;
	size_t		len;
	int			i;

	ex = init_expand(envp, last_status, 0, 0);
	len = 0;
	i = 0;
	while (str[i])
		len += process_len_char(str, &i, &ex);
	return (len);
}
