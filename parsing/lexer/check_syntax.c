/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 10:36:32 by byonis            #+#    #+#             */
/*   Updated: 2026/05/06 14:20:53 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	first_quote(char *line)
{
	int		i;

	i = 0;
	while (line && line[i] && line[i] != '"' && line[i] != '\'')
		i++;
	return (i);
}

static int	next_quote(char *line)
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

static int	check_start_pipe(char *line, int *i)
{
	*i = skip_spaces(line);
	if (line[*i] == '|')
	{
		ft_putstr_fd("Syntax Error: Pipe\n", 2);
		return (0);
	}
	return (1);
}

static int	process_syntax(char *line, int *i, int *last_was_pipe)
{
	int	next_pos;

	if (line[*i] == '"' || line[*i] == '\'')
	{
		next_pos = next_quote(line + *i);
		if (next_pos == -1)
			return (0);
		*i += next_pos + 1;
		*last_was_pipe = 0;
	}
	else if (line[*i] == '|')
	{
		if (*last_was_pipe)
			return (0);
		*last_was_pipe = 1;
		(*i)++;
	}
	else
	{
		if (!ft_isspace(line[*i]))
			*last_was_pipe = 0;
		(*i)++;
	}
	return (1);
}

int	check_syntax(char *line)
{
	int	i;
	int	last_was_pipe;

	i = skip_spaces(line);
	if (!check_start_pipe(line, &i))
		return (0);
	last_was_pipe = 0;
	while (line && line[i])
	{
		if (!process_syntax(line, &i, &last_was_pipe))
		{
			ft_putstr_fd("Syntax Error: Pipe or quote unclosed\n", 2);
			return (0);
		}
	}
	if (last_was_pipe)
	{
		ft_putstr_fd("Syntax Error: Pipe\n", 2);
		return (0);
	}
	return (1);
}
