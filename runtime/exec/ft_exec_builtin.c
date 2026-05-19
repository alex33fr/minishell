/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:45:28 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/09 16:17:02 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Return 1 if cmd name matches a known builtin, 0 otherwise.
 * @order 1.2.3.5.2.2.1
 */
int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/**
 * @brief
 * Dispatch argv[0] to the matching builtin handler, return its exit status.
 * @order 1.2.3.5.2.2.2
 */
int	ft_exec_builtin(t_cmd *cmd, t_env *env)
{
	int	status;

	if (!cmd->args || !cmd->args[0])
		return (1);
	status = 1;
	if (!ft_strcmp(cmd->args[0], "echo"))
		status = ft_builtin_echo(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		status = ft_builtin_cd(cmd->args, env);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		status = ft_builtin_pwd(env);
	else if (!ft_strcmp(cmd->args[0], "export"))
		status = ft_builtin_export(cmd->args, env);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		status = ft_builtin_unset(cmd->args, env);
	else if (!ft_strcmp(cmd->args[0], "env"))
		status = ft_builtin_env(env);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		status = ft_builtin_exit(cmd, env);
	return (status);
}
