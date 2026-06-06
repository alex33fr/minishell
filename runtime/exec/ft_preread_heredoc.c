/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preread_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 11:04:17 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/05 17:48:41 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Open a pipe for one heredoc, fill it via ft_heredoc_loop, store the read fd.
 * Returns 1 immediately if g_signal is set before starting the heredoc.
 * Also returns 1 (and closes the read end) if SIGINT fires during reading:
 * without this second check the pipeline would fork and execute even though
 * the heredoc was interrupted, running the commands with an empty stdin.
 * @order 1.2.3.5.3.2.1.1
 */
static int	ft_read_one_heredoc(t_redir *redir, t_env *env)
{
	int	pipefd[2];
	int	status;

	if (g_signal)
		return (1);
	status = pipe(pipefd);
	if (status == -1)
		return (1);
	ft_heredoc_loop(pipefd[1], redir->file, env, redir->heredoc_quoted);
	ft_close(pipefd[1], -1);
	if (g_signal)
	{
		ft_close(pipefd[0], -1);
		return (1);
	}
	redir->fd = pipefd[0];
	return (0);
}

/**
 * @brief
 * Pre-read every heredoc of one command into its pipe. Return 1 on interrupt.
 * @order 1.2.3.5.3.2.1
 */
static int	ft_read_cmd_heredocs(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	int		status;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == T_HEREDOC)
		{
			status = ft_read_one_heredoc(redir, env);
			if (status)
				return (1);
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
