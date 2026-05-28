/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:34:34 by byonis            #+#    #+#             */
/*   Updated: 2026/05/28 13:44:01 by byonis           ###   ########.fr       */
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
	int		i;
	int		j;
	int		quote;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (res && str[i])
	{
		if ((!quote && (str[i] == '\'' || str[i] == '"'))
			|| (quote && str[i] == quote))
			quote_def(&quote, str[i++]);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

// void	remove_quotes_delimiter(t_node *node)
// {
// 	char	*res;

// 	if (!node || !node->value)
// 		return ;
// 	res = unquoted(node->value);
// 	free(node->value);
// 	node->value = res;
// }
