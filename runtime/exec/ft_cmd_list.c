/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:47:05 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/19 16:52:36 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Restore saved stdin/stdout and close the saved fds.
 * @order 1.2.3.5.2.2.1
 */
static void	ft_restore_fds(t_cmd *cmd)
{
	dup2(cmd->saved_in, STDIN_FILENO);
	dup2(cmd->saved_out, STDOUT_FILENO);
	ft_close(cmd->saved_in, cmd->saved_out);
}

/**
 * @brief
 * Pre-read heredocs and apply redirs, then exec cmd. Return 130/1/status.
 * @order 1.2.3.5.2.2
 */
static int	ft_exec_redir(t_cmd *cmd, t_env *env)
{
	int	status;

	status = ft_preread_heredocs(cmd, env);
	if (status)
	{
		ft_close_heredoc_fds(cmd, NULL);
		ft_restore_fds(cmd);
		return (130);
	}
	status = ft_apply_redirs(cmd->redir);
	if (status)
	{
		ft_close_heredoc_fds(cmd, NULL);
		ft_restore_fds(cmd);
		return (1);
	}
	status = ft_exec_cmd(cmd, env);
	ft_restore_fds(cmd);
	return (status);
}

/**
 * @brief
 * Save stdin/stdout, then exec directly (no redir) or via ft_exec_redir.
 * @order 1.2.3.5.2
 */
static int	ft_exec_single(t_cmd *cmd, t_env *env)
{
	int	status;

	if (!cmd->redir)
	{
		status = ft_exec_cmd(cmd, env);
		return (status);
	}
	cmd->saved_in = dup(STDIN_FILENO);
	cmd->saved_out = dup(STDOUT_FILENO);
	status = ft_exec_redir(cmd, env);
	return (status);
}

/**
 * @brief
 * Return the number of commands in the list.
 * @order 1.2.3.5.1
 */
static int	ft_count_cmds(t_cmd *cmds)
{
	int	n;

	n = 0;
	while (cmds)
	{
		n++;
		cmds = cmds->next;
	}
	return (n);
}

/**
 * @brief
 * Dispatch a command list: single cmd runs in parent, multiple cmds as pipeline.
 * @order 1.2.3.5
 */
int	ft_exec_cmd_list(t_cmd *cmds, t_env *env, int last_status)
{
	int	n;
	int	ret;

	(void)last_status;
	if (!cmds)
		return (0);
	n = ft_count_cmds(cmds);
	if (n == 1)
		ret = ft_exec_single(cmds, env);
	else
		ret = ft_exec_pipeline(cmds, n, env);
	return (ret);
}
