/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:13:42 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/15 15:15:18 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Pre-read all heredocs in the command list and store their content in pipes.
 * @order 1.2.3.5.3.2
 */
int	ft_preread_heredocs(t_cmd *cmds)
{
	t_redir	*redir;
	int		pipefd[2];

	if (!cmds)
		return (0);
	while (cmds)
	{
		redir = cmds->redir;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				if (pipe(pipefd) == -1)
					return (1);
				ft_heredoc_loop(pipefd[1], redir->file);
				ft_close(pipefd[1], -1);
				redir->fd = pipefd[0];
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
