/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/18 00:00:00 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Read one line from stdin character by character. Return NULL on EOF.
 * @order 1.2.1 / 1.2.3.5.2.1.4.1.1
 */
char	*ft_read_heredoc_line(void)
{
	char	buf[4096];
	char	c;
	char	*res;
	int		i;
	int		r;

	i = 0;
	while (i < 4095)
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r <= 0)
			break ;
		if (c == '\n')
			break ;
		buf[i++] = c;
	}
	if (r <= 0 && i == 0)
		return (NULL);
	buf[i] = '\0';
	res = ft_strdup(buf);
	if (!res)
		return (NULL);
	return (res);
}

/**
 * @brief
 * Read lines until delimiter, write to a pipe, redirect stdin from it (<< delim)
 * Returns 0 on success, 1 on error
 * @param delimiter
 * @return int
 * @order 1.2.3.5.2.1.4
 */
int	ft_redir_heredoc(char *delimiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	ft_heredoc_loop(pipefd[1], delimiter);
	ft_close(pipefd[1], -1);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		ft_close(pipefd[0], -1);
		return (1);
	}
	ft_close(pipefd[0], -1);
	return (0);
}
