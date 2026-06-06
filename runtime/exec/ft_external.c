/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_external.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:41:06 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/06 11:44:46 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Close parent's saved fds, resolve path, then execve. Never returns.
 * @order 1.2.3.5.2.2.3.1
 */
static void	ft_run_process(t_exec *exec)
{
	char	*path;
	int		saved_in;
	int		saved_out;

	ft_signals_child();
	saved_in = exec->cmd->saved_in;
	saved_out = exec->cmd->saved_out;
	if (saved_in > STDERR_FILENO)
		close(saved_in);
	if (saved_out > STDERR_FILENO)
		close(saved_out);
	path = ft_resolve_path(exec);
	ft_exec_child(exec, path);
}

/**
 * @brief
 * Fork and execute an external command. Return exit code of the child.
 * @order 1.2.3.5.2.2.3
 */
int	ft_exec_external(t_cmd *cmd, t_env *env)
{
	t_exec	exec;
	pid_t	pid;
	int		ret;

	if (!cmd->args || !cmd->args[0] || !env)
		return (1);
	exec.argv = cmd->args;
	exec.env = env;
	exec.cmd = cmd;
	exec.envp = ft_env_to_envp(env);
	exec.pids = NULL;
	if (!exec.envp)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		ft_free_tab(exec.envp);
		return (1);
	}
	if (pid == 0)
		ft_run_process(&exec);
	ft_free_tab(exec.envp);
	ret = ft_wait_child(pid);
	return (ret);
}
