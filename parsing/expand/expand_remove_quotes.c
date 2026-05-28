/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_remove_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 11:52:08 by byonis            #+#    #+#             */
/*   Updated: 2026/05/28 13:19:53 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*expand_and_remove_quotes(char *str, char **envp, int last_status)
{
	t_expand	ex;
	char		*res;
	size_t		final_len;
	int			i;

	if (!str)
		return (NULL);
	final_len = get_expanded_len(str, envp, last_status);
	res = malloc(sizeof(char) * (final_len + 1));
	if (!res)
		return (NULL);
	ex = init_expand(envp, last_status, 0, 0);
	ex.res = res;
	ex.j = 0;
	i = 0;
	while (str[i])
	{
		if (!process_char(str, &i, &ex))
			return (NULL);
	}
	ex.res[ex.j] = '\0';
	return (ex.res);
}
