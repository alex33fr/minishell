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
 * 
 * @param pids 
 * @param n_cmds 
 * @return int 
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
 * 
 * @param cmd 
 * @param env 
 * @param fds 
 */
void	ft_child(t_cmd *cmd, t_env *env, t_pipe_fds *fds)
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
	exec.env = env;
	if (ft_is_builtin(cmd->args[0]))
		exit(ft_exec_builtin(cmd->args, env));
	envp = ft_env_to_envp(env);
	path = ft_resolve_path(&exec);
	ft_exec_child(&exec, path, envp);
}

/**
 * @brief 
 * 
 * @param fds 
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
