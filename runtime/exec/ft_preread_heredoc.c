/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preread_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 11:04:17 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/05 17:00:30 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Open a pipe per heredoc in cmd, fill it via ft_heredoc_loop, store fd.
 * Returns 1 immediately if g_signal is set before starting a heredoc.
 * Also returns 1 (and closes the read end) if SIGINT fires during reading:
 * without this second check the pipeline would fork and execute even though
 * the heredoc was interrupted, running the commands with an empty stdin.
 * @order 1.2.3.5.3.2.1
 */
static int	ft_read_cmd_heredocs(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	int		pipefd[2];
	int		status;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == T_HEREDOC)
		{
			if (g_signal)
				return (1);
			status = pipe(pipefd);
			if (status == -1)
				return (1);
			fcntl(pipefd[0], F_SETFD, FD_CLOEXEC);
			ft_heredoc_loop(pipefd[1], redir->file, env);
			ft_close(pipefd[1], -1);
			if (g_signal)
			{
				ft_close(pipefd[0], -1);
				return (1);
			}
			redir->fd = pipefd[0];
		}
		redir = redir->next;
	}
	return (0);
}

/**
 * @brief
 * Pre-read all heredocs in the command list and store their content in pipes.
 * Returns 1 immediately if g_signal is set (SIGINT).
 * @order 1.2.3.5.3.2
 */
int	ft_preread_heredocs(t_cmd *cmds, t_env *env)
{
	int	err;

	if (!cmds)
		return (0);
	while (cmds)
	{
		err = ft_read_cmd_heredocs(cmds, env);
		if (err)
			return (1);
		cmds = cmds->next;
	}
	return (0);
}
