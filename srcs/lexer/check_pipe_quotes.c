/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 10:36:32 by byonis            #+#    #+#             */
/*   Updated: 2026/04/23 12:51:11 by byonis           ###   ########.fr       */
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

static int	check_pipe(char *line)
{
	size_t	len;
	int		i;
	int		next_char;

	i = 0;
	if (!line)
		return (0);
	len = ft_strlen(line);
	if (line[0] == '|')
		return (0);
	while (line[i])
	{
		next_char = i + 1 + skip_spaces(line + i + 1);
		if (line[i] == '|' && line[next_char] == '|')
			return (0);
		i++;
	}
	if (line[len - 1] == '|')
		return (0);
	return (1);
}

static int	first_quote(char *line)
{
	int		i;

	i = 0;
	while (line && line[i] && line[i] != '"' && line[i] != '\'')
		i++;
	return (i);
}

static int	check_quotes(char *line)
{
	int		i;
	int		j;
	char	quote;

	i = first_quote(line);
	if (line[i] == '\0')
		return (i);
	quote = line[i];
	j = i + 1;
	while (line && line[j])
	{
		if (line[j] == quote)
			return (j);
		j++;
	}
	ft_putstr_fd("Syntax Error: Unclosed quotes\n", 2);
	return (-1);
}

int	check_pipe_quotes(char *line)
{
	int	i;
	int	next_pos;

	i = 0;
	if (!check_pipe(line))
	{
		ft_putstr_fd("Syntax Error: Pipe\n", 2);
		return (0);
	}
	while (line && line[i])
	{
		next_pos = check_quotes(line + i);
		if (next_pos == -1)
			return (0);
		i += next_pos;
		if (line[i])
			i++;
	}
	return (1);
}
