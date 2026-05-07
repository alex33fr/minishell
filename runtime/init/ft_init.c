/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:26:31 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/14 12:26:45 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Initialize shell: env from envp + setup signals
 * @order 1.1
 */
t_shell	*ft_init(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = ft_env_init(envp);
	if (!shell->env)
	{
		free(shell);
		return (NULL);
	}
	ft_setup_signals();
	return (shell);
}
