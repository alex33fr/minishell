/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 10:36:32 by byonis            #+#    #+#             */
/*   Updated: 2026/05/12 13:51:21 by byonis           ###   ########.fr       */
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

static int	error_syntax(char *line, char *token)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("' `", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

static int	check_start_pipe(char *line, int *i)
{
	*i = skip_spaces(line);
	if (line[*i] == '|')
		return (error_syntax(line, "|"));
	return (1);
}

static void	get_redir_str(char *line, int i, char *buf)
{
	if (line[i] == '<' && line[i + 1] == '<')
		ft_strlcpy(buf, "<<", 3);
	else if (line[i] == '>' && line[i + 1] == '>')
		ft_strlcpy(buf, ">>", 3);
	else if (line[i] == '<')
		ft_strlcpy(buf, "<", 2);
	else
		ft_strlcpy(buf, ">", 2);
}

static int	process_syntax(char *line, int *i, int *l_w_pipe, int *l_w_redir)
{
	char	buf[3];
	char	next_buf[3];
	int		next_pos;

	if (line[*i] == '"' || line[*i] == '\'')
	{
		next_pos = next_quote(line + *i);
		if (next_pos == -1)
			return (0);
		*i += next_pos + 1;
		*l_w_pipe = 0;
		*l_w_redir = 0;
	}
	else if (line[*i] == '|')
	{
		if (*l_w_pipe || *l_w_redir)
			return (error_syntax(line, "|"));
		*l_w_pipe = 1;
		*l_w_redir = 0;
		(*i)++;
	}
	else if (line[*i] == '<' || line[*i] == '>')
	{
		get_redir_str(line, *i, buf);
		if (*l_w_redir)
			return (error_syntax(line, buf));
		if (line[*i + 1] == line[*i])
			(*i)++;
		if (line[*i + 1] == '>' || line[*i + 1] == '<')
		{
			get_redir_str(line, *i + 1, next_buf);
			return (error_syntax(line, next_buf));
		}
		*l_w_pipe = 0;
		*l_w_redir = 1;
		(*i)++;
	}
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
	int last_was_redir;

	i = skip_spaces(line);
	if (!check_start_pipe(line, &i))
		return (0);
	last_was_pipe = 0;
	last_was_redir = 0;
	while (line && line[i])
	{
		if (!process_syntax(line, &i, &last_was_pipe, &last_was_redir))
		{
			ft_putstr_fd("Syntax Error\n", 2);
			return (0);
		}
	}
	if (last_was_pipe || last_was_redir)
		return (error_syntax(line, "newline"));
	return (1);
}
