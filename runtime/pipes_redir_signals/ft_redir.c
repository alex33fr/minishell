/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/27 11:30:52 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @return char* 
 */
static char	*ft_read_heredoc_line(void)
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
	return (res);
}

/**
 * @brief 
 * 
 * @param fd 
 * @param delimiter 
 */
static void	ft_heredoc_loop(int fd, char *delimiter)
{
	char	*line;
	int		size;

	while (1)
	{
		line = ft_read_heredoc_line();
		if (!line)
		{
			ft_putstr_fd("warning: heredoc delimited by EOF\n", 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		size = ft_strlen(line);
		write(fd, line, size);
		write(fd, "\n", 1);
		free(line);
	}
}

/**
 * @brief
 * Read lines until delimiter, write to a pipe, redirect stdin from it (<< delim)
 * Returns 0 on success, 1 on error
 * @param delimiter
 * @return int
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
