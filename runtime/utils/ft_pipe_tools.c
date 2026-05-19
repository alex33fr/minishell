/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:14:56 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/19 16:10:09 by aprivalo         ###   ########.fr       */
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
