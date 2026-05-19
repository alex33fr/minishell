/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:01:27 by byonis            #+#    #+#             */
/*   Updated: 2026/05/19 11:07:51 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_expand	init_expand(char **envp, int l_status, int squote, int dquote)
{
	t_expand	res;

	res.envp = envp;
	res.last_status = l_status;
	res.in_dquote = dquote;
	res.in_squote = squote;
	return (res);
}

static int	is_dollar_expand(char *str, int i, t_expand *ex)
{
	if (!str[i])
		return (0);
	if (str[i] == '$' && !ex->in_squote && str[i + 1]
		&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		return (1);
	return (0);
}

static int	manage_dollar_before_quote(char *str, int *i, t_expand *ex)
{
	if (str[*i] == '$' && (str[*i + 1] == '"' || str[*i + 1] == '\'')
		&& !ex->in_dquote && !ex->in_squote)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

static int	manage_quotes(char *str, int *i, t_expand *ex)
{
	if (str[*i] == '\'' && !ex->in_dquote)
	{
		ex->in_squote = !ex->in_squote;
		(*i)++;
		return (1);
	}
	else if (str[*i] == '"' && ! ex->in_squote)
	{
		ex->in_dquote = !ex->in_dquote;
		(*i)++;
		return (1);
	}
	return (0);
}

char	*process_char(char *str, int *i, t_expand *ex, char *res)
{
	char	buf[2];

	buf[1] = '\0';
	if (manage_dollar_before_quote(str, i, ex) || manage_quotes(str, i, ex))
		return (res);
	else if (is_dollar_expand(str, *i, ex))
		res = handle_dollar(str, i, ex, res);
	else if (str[*i] == '\\' && !ex->in_squote && !ex->in_dquote)
	{
		(*i)++;
		if (str[*i])
		{
			buf[0] = str[*i];
			res = append(res, buf);
			(*i)++;
		}
	}
	else
	{
		buf[0] = str[*i];
		res = append(res, buf);
		(*i)++;
	}
	return (res);
}
