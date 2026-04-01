/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:41:48 by byonis            #+#    #+#             */
/*   Updated: 2026/04/01 14:41:46 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	get_first_word_len(char *line)
{
	int		res;
	char	quote;

	res = 0;
	while (line[res] && !ft_isspace(line[res])
		&& line[res] != '<' && line[res] != '>' && line[res] != '|')
	{	
		if (line[res] == '"' || line[res] == '\'')
		{
			quote = line[res++];
			while (line[res] && line[res] != quote)
				res++;
			if (line[res] == quote)
				res++;
		}
		else
			res++;
	}
	return (res);
}

int	next_token(char *line, t_tok tok)
{
	int		res;
	char	quote;

	res = 0;
	if (tok == T_WORD)
		return (get_first_word_len(line));
	else if (tok == T_REDIRIN || tok == T_PIPE || tok == T_REDIROUT)
		res = 1;
	else
		res = 2;
	return (res);
}

static int	find_quote_end(char *line, int i)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		i++;
	return (i);
}

char	*first_word(char *line)
{
	char	*result;
	char	quote;
	int		i;
	int		j;
	int		end;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (next_token(line, T_WORD) + 1));
	if (!result)
		return (NULL);
	while (i < next_token(line, T_WORD))
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			end = find_quote_end(line, i);
			while (++i < end - 1)
				result[j++] = line[i];
			i++;
		}
		else
			result[j++] = line[i++];
	}
	result[j] = '\0';
	return (result);
}
