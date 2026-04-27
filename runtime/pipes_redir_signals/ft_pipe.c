/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 09:01:00 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/27 12:09:01 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param cmd 
 * @param env 
 * @param fds 
 * @return int 
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
 * 
 * @param fds 
 */
static void	ft_fds_init(t_pipe_fds *fds)
{
	fds->prev_fd = -1;
	fds->pipefd[0] = -1;
	fds->pipefd[1] = -1;
}

/**
 * @brief 
 * 
 * @param cmds 
 * @param env 
 * @param fds 
 * @param pid 
 * @return int 
 */
static int	ft_iter_cmd(t_cmd **cmds, t_env *env, t_pipe_fds *fds, pid_t *pid)
{
	if (!fds->last && pipe(fds->pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	*pid = ft_fork(*cmds, env, fds);
	if (*pid < 0)
		return (-1);
	ft_update_fds(fds);
	*cmds = (*cmds)->next;
	return (0);
}
/**
 * @brief 
 * 
 * @param cmds 
 * @param n_cmds 
 * @param env 
 * @param pids 
 * @return int 
 */

static int	ft_fork_loop(t_cmd *cmds, int n_cmds, t_env *env, pid_t *pids)
{
	t_pipe_fds	fds;
	int			i;

	ft_fds_init(&fds);
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
 * 
 * @param cmds 
 * @param n_cmds 
 * @param env 
 * @return int 
 */
int	ft_exec_pipeline(t_cmd *cmds, int n_cmds, t_env *env)
{
	pid_t	*pids;
	int		ret;

	pids = malloc(sizeof(pid_t) * n_cmds);
	if (!pids)
		return (1);
	if (ft_fork_loop(cmds, n_cmds, env, pids))
	{
		free(pids);
		return (1);
	}
	ret = ft_wait_all(pids, n_cmds);
	free(pids);
	return (ret);
}
