/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:41:48 by byonis            #+#    #+#             */
/*   Updated: 2026/05/06 14:09:45 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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

	res = 0;
	if (tok == T_WORD)
		return (get_first_word_len(line));
	else if (tok == T_REDIRIN || tok == T_PIPE || tok == T_REDIROUT)
		res = 1;
	else
		res = 2;
	return (res);
}

t_tok	get_token_type(char *line)
{
	if (line[0] == '<')
	{
		if (line[1] == '<')
			return (T_HEREDOC);
		return (T_REDIRIN);
	}
	else if (line[0] == '>')
	{
		if (line[1] == '>')
			return (T_APPEND);
		return (T_REDIROUT);
	}
	else if (line[0] == '|')
		return (T_PIPE);
	else
		return (T_WORD);
}

char	*first_word(char *line)
{
	char	*result;
	int		len;

	if (!line)
		return (NULL);
	len = next_token(line, T_WORD);
	result = ft_substr(line, 0, len);
	return (result);
}

t_queue	*do_expand(t_queue *q, char **envp, int last_status)
{
	t_node	*temp;
	char	*res;

	temp = q->front;
	while (temp->token != T_EOF)
	{
		if (temp->token == T_WORD)
		{
			res = expand(temp->value, envp, last_status);
			if (!res)
				return (NULL);
			free(temp->value);
			temp->value = res;
		}
		temp = temp->next;
	}
	return (q);
}
