/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 10:36:32 by byonis            #+#    #+#             */
/*   Updated: 2026/05/15 10:28:46 by aprivalo         ###   ########.fr       */
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

int	next_quote(char *line)
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
		return (error_syntax(line, "|"));
	return (1);
}

static int	process_syntax(char *line, int *i, int *l_w_pipe, int *l_w_redir)
{
	if (line[*i] == '"' || line[*i] == '\'')
		return (manage_syntax_quotes(line, i, l_w_pipe, l_w_redir));
	if (line[*i] == '|')
	{
		if (*l_w_pipe || *l_w_redir)
			return (error_syntax(line, "|"));
		*l_w_pipe = 1;
		*l_w_redir = 0;
		(*i)++;
	}
	else if (line[*i] == '<' || line[*i] == '>')
		return (manage_syntax_redir(line, i, l_w_pipe, l_w_redir));
	else if (line[*i] == ';')
		return (error_syntax(line, ";"));
	else
	{
		if (!ft_isspace(line[*i]))
		{
			*l_w_pipe = 0;
			*l_w_redir = 0;
		}
		(*i)++;
	}
	return (1);
}

int	check_syntax(char *line)
{
	int	i;
	int	last_was_pipe;
	int	last_was_redir;

	i = skip_spaces(line);
	if (!check_start_pipe(line, &i))
		return (0);
	last_was_pipe = 0;
	last_was_redir = 0;
	while (line && line[i])
	{
		if (!process_syntax(line, &i, &last_was_pipe, &last_was_redir))
			return (0);
	}
	if (last_was_pipe || last_was_redir)
		return (error_syntax(line, "newline"));
	return (1);
}
