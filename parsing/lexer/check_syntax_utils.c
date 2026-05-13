/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:36:18 by byonis            #+#    #+#             */
/*   Updated: 2026/05/13 13:23:14 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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

int	manage_syntax_quotes(char *line, int *i, int *l_wp, int *l_wr)
{
	int	next_pos;

	next_pos = next_quote(line + *i);
	if (next_pos == -1)
		return (0);
	*i += next_pos + 1;
	*l_wp = 0;
	*l_wr = 0;
	return (1);
}

int	manage_syntax_redir(char *line, int *i, int *l_wp, int *l_wr)
{
	char	buf[3];
	char	next_buf[3];

	get_redir_str(line, *i, buf);
	if (*l_wr)
		return (error_syntax(line, buf));
	if (line[*i + 1] == line[*i])
		(*i)++;
	if (line[*i + 1] == '>' | line[*i + 1] == '<')
	{
		get_redir_str(line, *i + 1, next_buf);
		return (error_syntax(line, next_buf));
	}
	*l_wp = 0;
	*l_wr = 1;
	(*i)++;
	return (1);
}

int	error_syntax(char *line, char *token)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("' `", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}
