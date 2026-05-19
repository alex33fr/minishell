/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:23:07 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/19 16:53:46 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Dispatch argv[0] to builtin or external, return its exit status.
 * @order 1.2.3.5.2.2
 */
int	ft_exec_cmd(t_cmd *cmd, t_env *env)
{
	int	status;

	if (!cmd->args || !cmd->args[0])
	if (!env)
		return (1);
	status = 1;
	if (ft_is_builtin(cmd->args[0]))
		status = ft_exec_builtin(cmd, env);
	else
		status = ft_exec_external(cmd, env);
	return (status);
}
