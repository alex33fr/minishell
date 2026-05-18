/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:34:34 by byonis            #+#    #+#             */
/*   Updated: 2026/05/13 11:19:45 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	has_quotes(char *str)
{
	if (!str)
		return (0);
	if (ft_strchr(str, '\''))
		return (1);
	return (0);
}

static void	quote_def(int *quote, char c)
{
	if (*quote == 0)
		*quote = c;
	else
		*quote = 0;
}

char	*unquoted(char *str)
{
	char	*res;
	char	buf[2];
	int		i;
	int		quote;

	res = ft_strdup("");
	buf[1] = '\0';
	i = 0;
	quote = 0;
	while (res && str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote_def(&quote, str[i++]);
		else if (quote && str[i] == quote)
			quote_def(&quote, str[i++]);
		else
		{
			buf[0] = str[i++];
			res = append(res, buf);
		}
	}
	return (res);
}

void	remove_quotes_delimiter(t_node *node)
{
	char	*res;

	res = unquoted(node->value);
	free(node->value);
	node->value = res;
}
