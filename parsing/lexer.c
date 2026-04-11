/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:18:39 by byonis            #+#    #+#             */
/*   Updated: 2026/04/11 13:47:19 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

static int	add_eof(t_queue *q)
{
	char	*end;

	end = ft_strdup("");
	if (!end)
		return (0);
	if (!enqueue(q, T_EOF, end))
	{
		free(end);
		return (0);
	}
	return (1);
}

static int	process_next_token(t_queue *q, char *line)
{
	t_tok	type;
	int		len;
	
	type = get_token_type(line);
	len = next_token(line, type);
	if (type == T_WORD)
	{
		if (!enqueue(q, type, first_word(line)))
			return (-1);
	}
	else
	{
		if (!search_token(q, line))
			return (-1);
	}
	return (len);
}

static int	tokenize_line(t_queue *q, char *line)
{
	int	i;
	int	len;

	i = 0;
	while (line[i])
	{
		i += skip_spaces(line + i);
		if (!line[i])
			break ;
		len = process_next_token(q, line + i);
		if (len == -1)
			return (0);
		i += len;
	}
	return (1);
}

t_queue	*lexer(char *line)
{
	t_queue	*tokens;

	if (!line)
		return (NULL);
	if (!check_pipe_quotes(line))
		return (NULL);
	tokens = empty_queue();
	if (!tokens)
		return (NULL);
	if (!tokenize_line(tokens, line) || !add_eof(tokens))
	{
		clear_queue(tokens);
		return (NULL);
	}
	// while (line[i])
	// {
	// 	i += skip_spaces(line + i);
	// 	if (!line[i])
	// 		break ;
	// 	type = get_token_type(line + i);
	// 	len = next_token(line + i, type);
	// 	if (type == T_WORD)
	// 	{
	// 		if (!enqueue(tokens, type, first_word(line + i)))
	// 		{
	// 			clear_queue(tokens);
	// 			return (NULL);
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if (!search_token(tokens, line + i))
	// 		{
	// 			clear_queue(tokens);
	// 			return (NULL);
	// 		}
	// 	}
	// 	i += len;
	// }
	if (!check_redir(tokens))
	{
		clear_queue(tokens);
		return (NULL);
	}
	return (tokens);
}
