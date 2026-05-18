/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 00:00:00 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/18 00:00:00 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Close all heredoc pipe fds in the cmd list, skipping one cmd if skip != NULL.
 * Used in parent after fork (skip=NULL) and in child for other cmds (skip=cmd).
 * @order 1.2.3.5.3.3
 */
void	ft_close_heredoc_fds(t_cmd *head, t_cmd *skip)
{
	t_redir	*redir;

	while (head)
	{
		if (head != skip)
		{
			redir = head->redir;
			while (redir)
			{
				if (redir->type == T_HEREDOC)
					ft_close(redir->fd, -1);
				redir = redir->next;
			}
		}
		head = head->next;
	}
}
