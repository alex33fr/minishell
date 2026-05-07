/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:14:56 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/27 11:31:32 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Wait for all n_cmds children, return exit status of the last one.
 * @order 1.2.3.5.3.2
 */
int	ft_wait_all(pid_t *pids, int n_cmds)
{
	int	i;
	int	status;
	int	last;

	i = 0;
	last = 0;
	while (i < n_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == n_cmds - 1 && WIFEXITED(status))
			last = WEXITSTATUS(status);
		i++;
	}
	return (last);
}

/**
 * @brief
 * Wire pipe fds, apply redirs, then exec builtin or external. Never returns.
 * @order 1.2.3.5.3.1.2.1.1
 */
void	ft_child(t_cmd *cmd, t_shell *shell, t_pipe_fds *fds)
{
	t_exec	exec;
	char	*path;
	char	**envp;

	ft_signals_child();
	if (fds->prev_fd != -1)
		dup2(fds->prev_fd, STDIN_FILENO);
	if (!fds->last)
		dup2(fds->pipefd[1], STDOUT_FILENO);
	ft_close(fds->prev_fd, -1);
	ft_close(fds->pipefd[0], fds->pipefd[1]);
	if (ft_apply_redirs(cmd->redir))
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	exec.argv = cmd->args;
	exec.env = shell->env;
	if (ft_is_builtin(cmd->args[0]))
		exit(ft_exec_builtin(cmd->args, shell));
	envp = ft_env_to_envp(shell->env);
	path = ft_resolve_path(&exec);
	ft_exec_child(&exec, path, envp);
}

/**
 * @brief
 * Close the write end of the current pipe and advance prev_fd to the read end.
 * @order 1.2.3.5.3.1.2.2
 */
void	ft_update_fds(t_pipe_fds *fds)
{
	ft_close(fds->prev_fd, -1);
	if (!fds->last)
		ft_close(fds->pipefd[1], -1);
	if (!fds->last)
		fds->prev_fd = fds->pipefd[0];
	else
		fds->prev_fd = -1;
}
