/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:13:42 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/18 00:00:00 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Write line + newline to fd, then free the line.
 * @order 1.2.3.5.2.1.4.1.0
 */
static void	ft_heredoc_write(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

/**
 * @brief
 * Set SIGINT handler to sig_int_heredoc via sigaction.
 * @order 1.2.3.5.2.1.4.1.3
 */
static void	ft_set_heredoc_sig(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_int_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

/**
 * @brief
 * Check stop conditions: signal, EOF, or delimiter match. Free line and return 1 to break.
 * @order 1.2.3.5.2.1.4.1.4
 */
static int	ft_heredoc_check(char *line, char *delimiter)
{
	if (g_signal)
	{
		free(line);
		return (1);
	}
	if (!line)
	{
		ft_err_1();
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

/**
 * @brief
 * Read lines from stdin and write them to fd until delimiter or EOF is seen.
 * @order 1.2.3.5.2.1.4.1
 */
void	ft_heredoc_loop(int fd, char *delimiter)
{
	char	*line;

	ft_set_heredoc_sig();
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = ft_read_heredoc_line();
		if (ft_heredoc_check(line, delimiter))
			break ;
		ft_heredoc_write(fd, line);
	}
	ft_setup_signals();
}

/**
 * @brief
 * Pre-read all heredocs in the command list and store their content in pipes.
 * @order 1.2.3.5.3.2
 */
int	ft_preread_heredocs(t_cmd *cmds)
{
	t_redir	*redir;
	int		pipefd[2];

	if (!cmds)
		return (0);
	while (cmds)
	{
		redir = cmds->redir;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				if (pipe(pipefd) == -1)
					return (1);
				ft_heredoc_loop(pipefd[1], redir->file);
				ft_close(pipefd[1], -1);
				redir->fd = pipefd[0];
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
