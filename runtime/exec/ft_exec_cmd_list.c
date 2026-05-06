/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 00:00:00 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/27 11:29:55 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param cmd 
 * @param env 
 * @return int 
 */
static int	ft_exec_single(t_cmd *cmd, t_env *env)
{
	int	saved_in;
	int	saved_out;
	int	status;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (ft_apply_redirs(cmd->redir))
	{
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		ft_close(saved_in, saved_out);
		return (1);
	}
	status = ft_exec_cmd(cmd->args, env);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	ft_close(saved_in, saved_out);
	return (status);
}

/**
 * @brief 
 * 
 * @param cmds 
 * @return int 
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
 * 
 * @param cmds 
 * @param env 
 * @param last_status 
 * @return int 
 */
int	ft_exec_cmd_list(t_cmd *cmds, t_env *env, int last_status)
{
	int		n;
	int		status;

	(void)last_status;
	if (!cmds)
		return (0);
	n = ft_count_cmds(cmds);
	if (n == 1)
	{
		status = ft_exec_single(cmds, env);
		return (status);
	}
	status = ft_exec_pipeline(cmds, n, env);
	return (status);
}
