/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:38:54 by byonis            #+#    #+#             */
/*   Updated: 2026/04/04 11:22:45 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

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
