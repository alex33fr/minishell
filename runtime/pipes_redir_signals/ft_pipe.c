/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 09:01:00 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/19 15:44:43 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Fork and run ft_child in the child process. Return pid, -1 on error.
 * @order 1.2.3.5.3.1.2.1
 */
static int	ft_fork(t_cmd *cmd, t_env *env, t_pipe_fds *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		ft_child(cmd, env, fds);
	return (pid);
}

/**
 * @brief
 * Initialize pipe fds struct with -1 (no fd open yet).
 * @order 1.2.3.5.3.1.1
 */
static void	ft_fds_init(t_pipe_fds *fds)
{
	fds->prev_fd = -1;
	fds->pipefd[0] = -1;
	fds->pipefd[1] = -1;
}

/**
 * @brief
 * Open a pipe if not last cmd, fork, advance cmds. Return 0 or -1 on error.
 * @order 1.2.3.5.3.1.2
 */
static int	ft_iter_cmd(t_cmd **cmds, t_env *env, t_pipe_fds *fd, pid_t *pid)
{
	if (!fd->last && pipe(fd->pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	*pid = ft_fork(*cmds, env, fd);
	if (*pid < 0)
		return (-1);
	ft_update_fds(fd);
	*cmds = (*cmds)->next;
	return (0);
}

/**
 * @brief
 * Fork all pipeline commands, store pids. Return 1 on error.
 * @order 1.2.3.5.3.1
 */
static int	ft_fork_loop(t_cmd *cmds, int n_cmds, t_env *env, pid_t *pids)
{
	t_pipe_fds	fds;
	int			i;

	ft_fds_init(&fds);
	fds.pids = pids;
	i = 0;
	while (cmds && i < n_cmds)
	{
		fds.last = (i == n_cmds - 1);
		if (ft_iter_cmd(&cmds, env, &fds, &pids[i]) < 0)
		{
			ft_wait_all(pids, i);
			return (1);
		}
		i++;
	}
	ft_close(fds.prev_fd, -1);
	return (0);
}

/**
 * @brief
 * Execute a pipeline of n_cmds commands, wait for all children.
 * Returns 130 if heredoc reading was interrupted by SIGINT.
 * @order 1.2.3.5.3
 */
int	ft_exec_pipeline(t_cmd *cmds, int n_cmds, t_env *env)
{
	pid_t	*pids;
	int		ret;

	pids = malloc(sizeof(pid_t) * n_cmds);
	if (!pids)
		return (130);
	if (ft_preread_heredocs(cmds, env))
	{
		ft_close_heredoc_fds(cmds, NULL);
		free(pids);
		return (0);
	}
	if (ft_fork_loop(cmds, n_cmds, env, pids))
	{
		free(pids);
		return (1);
	}
	ft_close_heredoc_fds(cmds, NULL);
	ret = ft_wait_all(pids, n_cmds);
	free(pids);
	return (ret);
}
