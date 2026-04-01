/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:18:39 by byonis            #+#    #+#             */
/*   Updated: 2026/04/01 13:37:03 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

// < infile cmd1 | cmd2 > outfile
// < infile
// cmd1
// |
// cmd2
// > outfile

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

t_queue	*lexer(char *line)
{
	t_queue	*tokens;
	int		i;
	int		len;
	char	*end;

	i = 0;
	if (!line)
		return (NULL);
	tokens = empty_queue();
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		i += skip_spaces(line + i);
		if (!line[i])
			break ;
		if (!search_token(tokens, line + i))
		{
			clear_queue(tokens);
			return (NULL);
		}
		i += next_token(line + i, tokens->back->token);
	}
	end = ft_strdup("");
	if (!end)
	{
		clear_queue(tokens);
		return (NULL);
	}
	enqueue(tokens, T_EOF, end);
	return (tokens);
}
