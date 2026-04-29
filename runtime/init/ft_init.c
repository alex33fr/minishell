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
