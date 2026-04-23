/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:08:48 by byonis            #+#    #+#             */
/*   Updated: 2026/04/23 12:53:57 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static void	free_args(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_redir(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		temp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = temp;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*temp;

	while (cmds)
	{
		temp = cmds->next;
		if (cmds->args)
			free_args(cmds->args);
		if (cmds->redir)
			free_redir(cmds->redir);
		free(cmds);
		cmds = temp;
	}
}
