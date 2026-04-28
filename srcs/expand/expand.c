/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:12:57 by byonis            #+#    #+#             */
/*   Updated: 2026/04/28 15:45:04 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h" 

static void	clear_pre_suf(char *prefix, char *suffix, char *v_replaced)
{
	free(prefix);
	free(suffix);
	free(v_replaced);
}

static char	*replace(char *str, char *var_replaced, int pos)
{
	char	*res;
	char	*prefix;
	char	*suffix;
	char	*mid;

	mid = var_extraction(str, pos);
	if (!mid)
		return (NULL);
	prefix = ft_substr(str, 0, pos);
	suffix = ft_strdup(&str[pos + 1 + ft_strlen(mid)]);
	res = NULL;
	if (prefix && suffix)
	{
		res = ft_strjoin_m(prefix, var_replaced);
		res = ft_strjoin_m(res, suffix);
	}
	else
		clear_pre_suf(prefix, suffix, var_replaced);
	free(mid);
	return (res);
}

static char	*process_expansion(char *res, char **envp, int *i)
{
	char	*value;
	char	*temp;
	int		val_len;

	val_len = 0;
	value = var_replaced(res, envp, *i); // rajouter int last_status
	if (!value)
	{
		free(res);
		return (NULL);
	}
	val_len = ft_strlen(value);
	temp = replace(res, value, *i);
	if (!temp)
	{
		free(res);
		return (NULL);
	}
	*i += val_len;
	free(res);
	return (temp);
}

char	*remove_quotes(char *str)
{
	int	i;
	int	j;
	int	in_squote;
	int	in_dquote;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

char *expand(char *str, char **envp) // rajouter int last_status
{
	char	*res;
	int		i;
	int		in_double_quotes;
	
	if (!str)
		return (NULL);
	res = ft_strdup(str);
	if (!res)
		return (NULL);
	i = 0;
	in_double_quotes = 0;
	i = find_the_next_valid_variable(res, i, &in_double_quotes);
	while (i != -1)
	{
		res = process_expansion(res, envp, &i); // rajouter int last_status
		if (!res)
			break ;
		i = find_the_next_valid_variable(res, i, &in_double_quotes);
	}
	// remove_quotes(res);
	return (res);
}
