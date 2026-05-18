/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 00:00:00 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/18 18:40:20 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Save stdin/stdout in cmd, apply redirs, run cmd, restore fds.
 * Return cmd exit status, 1 on redir error.
 * @order 1.2.3.5.2
 */
static int	ft_exec_single(t_cmd *cmd, t_env *env)
{
	int	status;

	cmd->saved_in = dup(STDIN_FILENO);
	cmd->saved_out = dup(STDOUT_FILENO);
	ft_preread_heredocs(cmd, env);
	if (ft_apply_redirs(cmd->redir, env))
	{
		dup2(cmd->saved_in, STDIN_FILENO);
		dup2(cmd->saved_out, STDOUT_FILENO);
		ft_close(cmd->saved_in, cmd->saved_out);
		return (1);
	}
	status = ft_exec_cmd(cmd, env);
	dup2(cmd->saved_in, STDIN_FILENO);
	dup2(cmd->saved_out, STDOUT_FILENO);
	ft_close(cmd->saved_in, cmd->saved_out);
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
