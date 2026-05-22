/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:28:36 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/19 14:40:04 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
static void	ft_child_setup_pipes(t_pipe_fds *fds)
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
 * Initialize t_exec fields from cmd, fds, env.
 * @order 1.2.3.5.3.1.2.1.3
 */
static void	ft_child_init_exec(t_exec *exec, t_cmd *cmd,
				t_pipe_fds *fds, t_env *env)
{
	exec->argv = cmd->args;
	exec->env = env;
	exec->cmd = cmd;
	exec->pids = fds->pids;
	exec->envp = NULL;
}

/**
 * @brief
 * Close heredoc fds from all cmds except the current one.
 * @order 1.2.3.5.3.1.2.1.4
 */
static void	ft_child_close_heredocs(t_cmd *cmd)
{
	t_cmd	*head;

	head = cmd;
	while (head->prev)
		head = head->prev;
	ft_close_heredoc_fds(head, cmd);
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

	ft_child_init_exec(&exec, cmd, fds, env);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_child_setup_pipes(fds);
	ft_child_close_heredocs(cmd);
	ret = ft_apply_redirs(cmd->redir, env);
	if (ret)
		ft_builtin_child_exit(&exec, 1);
	if (!cmd->args || !cmd->args[0])
		ft_builtin_child_exit(&exec, 0);
	ret = ft_is_builtin(cmd->args[0]);
	if (ret)
	{
		ret = ft_exec_builtin(cmd, env);
		ft_builtin_child_exit(&exec, ret);
	}
	exec.envp = ft_env_to_envp(env);
	path = ft_resolve_path(&exec);
	ft_signals_child();
	ft_exec_child(&exec, path);
}
