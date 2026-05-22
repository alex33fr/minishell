/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:15:32 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/22 10:15:32 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Init env from envp and setup signal handlers.
 * @order 1.1
 */
t_env	*ft_init(char **envp)
{
	t_env	*env;

	env = ft_env_init(envp);
	if (!env)
		return (NULL);
	ft_setup_signals();
	return (env);
}

int	ft_exec_cmds(t_queue *tokens, char **pline, t_env *env, int ls)
{
	t_cmd	*cmds;

	cmds = create_cmds(tokens);
	clear_queue(tokens);
	free(*pline);
	*pline = NULL;
	if (!cmds)
		return (ls);
	ls = ft_exec_cmd_list(cmds, env, ls);
	free_cmds(cmds);
	return (ls);
}
