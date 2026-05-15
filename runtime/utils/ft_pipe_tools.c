/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:14:56 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/08 13:50:54 by aprivalo         ###   ########.fr       */
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
	ft_setup_signals_exec();
	while (i < n_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == n_cmds - 1)
		{
			if (WIFEXITED(status))
				last = WEXITSTATUS(status);
			else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				last = 130;
			else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				last = 131;
		}
		i++;
	}
	ft_setup_signals();
	return (last);
}

/**
 * @brief
 * Free child resources and exit with ret. Never returns.
 * @order 1.2.3.5.3.1.2.1.1
 */
static void	ft_builtin_child_exit(t_exec *exec, int ret)
{
	t_cmd	*head;

	head = exec->cmd;
	while (head->prev)
		head = head->prev;
	free(exec->pids);
	free_cmds(head);
	ft_env_clear(exec->env);
	exit(ret);
}

/**
 * @brief
 * Wire stdin/stdout to pipe fds then close unused ends.
 * @order 1.2.3.5.3.1.2.1.2
 */
static void	ft_setup_pipes(t_pipe_fds *fds)
{
	if (fds->prev_fd != -1)
		dup2(fds->prev_fd, STDIN_FILENO);
	if (!fds->last)
		dup2(fds->pipefd[1], STDOUT_FILENO);
	ft_close(fds->prev_fd, -1);
	if (!fds->last)
		ft_close(fds->pipefd[0], fds->pipefd[1]);
}

/**
 * @brief
 * Wire pipe fds, apply redirs, then exec builtin or external. Never returns.
 * @order 1.2.3.5.3.1.2.1
 */
void	ft_child(t_cmd *cmd, t_env *env, t_pipe_fds *fds)
{
	t_exec	exec;
	char	*path;
	int		ret;

	exec.argv = cmd->args;
	exec.env = env;
	exec.cmd = cmd;
	exec.pids = fds->pids;
	exec.envp = NULL;
	ft_signals_child();
	ft_setup_pipes(fds);
	if (ft_apply_redirs(cmd->redir))
		ft_builtin_child_exit(&exec, 1);
	if (!cmd->args || !cmd->args[0])
		ft_builtin_child_exit(&exec, 0);
	if (ft_is_builtin(cmd->args[0]))
	{
		ret = ft_exec_builtin(cmd, env);
		ft_builtin_child_exit(&exec, ret);
	}
	exec.envp = ft_env_to_envp(env);
	path = ft_resolve_path(&exec);
	ft_exec_child(&exec, path);
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
