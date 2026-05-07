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
 * Find builtin in cmd argv[0]
 * @param cmd
 * @return int
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
int	ft_exec_builtin(char **argv, t_shell *shell)
{
	int	status;

	if (!argv || !argv[0])
		return (1);
	status = 1;
	if (!ft_strcmp(argv[0], "echo"))
		status = ft_builtin_echo(argv);
	else if (!ft_strcmp(argv[0], "cd"))
		status = ft_builtin_cd(argv, shell->env);
	else if (!ft_strcmp(argv[0], "pwd"))
		status = ft_builtin_pwd();
	else if (!ft_strcmp(argv[0], "export"))
		status = ft_builtin_export(argv, shell->env);
	else if (!ft_strcmp(argv[0], "unset"))
		status = ft_builtin_unset(argv, shell->env);
	else if (!ft_strcmp(argv[0], "env"))
		status = ft_builtin_env(shell->env);
	else if (!ft_strcmp(argv[0], "exit"))
		status = ft_builtin_exit(argv, shell);
	return (status);
}
