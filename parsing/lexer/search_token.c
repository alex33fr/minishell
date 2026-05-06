/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:38:54 by byonis            #+#    #+#             */
/*   Updated: 2026/04/28 11:01:19 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	check_redir(t_queue *queue)
{
	t_node	*node;

	if (!queue || !queue->front)
		return (0);
	node = queue->front;
	while (node)
	{
		if (node->token == T_REDIRIN || node->token == T_REDIROUT
			|| node->token == T_APPEND || node->token == T_HEREDOC)
		{
			if (!node->next || node->next->token != T_WORD)
				return (0);
		}
		node = node->next;
	}
	return (1);
}

static int	search_pipe(t_queue *q, char *line)
{
	char	*result;

	if (line[0] == '|')
	{
		result = ft_strdup("|");
		if (!result || !enqueue(q, T_PIPE, result))
		{
			free(result);
			return (0);
		}
	}
	return (1);
}

static int	search_redirin(t_queue *q, char *line)
{
	char	*result;

	if (line[0] == '<')
	{
		if (line[1] == '<')
		{
			result = ft_strdup("<<");
			if (!result || !enqueue(q, T_HEREDOC, result))
			{
				free(result);
				return (0);
			}
		}
		else
		{
			result = ft_strdup("<");
			if (!result || !enqueue(q, T_REDIRIN, result))
			{
				free(result);
				return (0);
			}
		}
	}
	return (1);
}

static int	search_redirout(t_queue *q, char *line)
{
	char	*result;

	if (line[0] == '>')
	{
		if (line[1] == '>')
		{
			result = ft_strdup(">>");
			if (!result || !enqueue(q, T_APPEND, result))
			{
				free(result);
				return (0);
			}
		}
		else
		{
			result = ft_strdup(">");
			if (!result || !enqueue(q, T_REDIROUT, result))
			{
				free(result);
				return (0);
			}
		}
	}
	return (1);
}

int	search_token(t_queue *q, char *line)
{
	char	*result;

	if (line[0] == '<')
		return (search_redirin(q, line));
	else if (line[0] == '>')
		return (search_redirout(q, line));
	else if (line[0] == '|')
		return (search_pipe(q, line));
	else
	{
		result = first_word(line);
		if (!result || !enqueue(q, T_WORD, result))
		{
			free(result);
			return (0);
		}
	}
	return (1);
}
