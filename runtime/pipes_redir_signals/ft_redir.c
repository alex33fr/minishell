/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 09:41:07 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/05 11:26:49 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Read one heredoc line via readline (supports line editing). Return NULL on EOF.
 * Caller must free the result.
 * @order 1.2.1 / 1.2.3.5.2.1.4.1.1
 */
char	*ft_read_heredoc_line(void)
{
	char	*line;
	char	*res;

	line = readline("> ");
	if (!line)
		return (NULL);
	res = ft_strdup(line);
	free(line);
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
int	ft_redir_heredoc(char *delimiter, t_env *env)
{
	int	pipefd[2];
	int	status;

	status = pipe(pipefd);
	if (status == -1)
	{
		perror("pipe");
		return (1);
	}
	ft_heredoc_loop(pipefd[1], delimiter, env);
	ft_close(pipefd[1], -1);
	status = dup2(pipefd[0], STDIN_FILENO);
	if (status < 0)
	{
		perror("dup2");
		ft_close(pipefd[0], -1);
		return (1);
	}
	ft_close(pipefd[0], -1);
	return (0);
}
