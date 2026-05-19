/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_remove_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 11:52:08 by byonis            #+#    #+#             */
/*   Updated: 2026/05/19 11:04:25 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*expand_and_remove_quotes(char *str, char **envp, int last_status)
{
	t_expand	ex;
	char		*res;
	int			i;

	ex = init_expand(envp, last_status, 0, 0);
	res = ft_strdup("");
	i = 0;
	while (res && str[i])
	{
		res = process_char(str, &i, &ex, res);
		if (!res)
			return (NULL);
	}
	return (res);
}
