/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:49:51 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/19 15:34:55 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Wait for child process and return its exit status
 * @param pid
 * @return int
 * @order 1.2.3.5.2.2.3.2
 */
int	ft_wait_child(pid_t pid)
{
	int	status;

	ft_setup_signals_exec();
	waitpid(pid, &status, 0);
	ft_setup_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (130);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 1);
		return (131);
	}
	return (1);
}
