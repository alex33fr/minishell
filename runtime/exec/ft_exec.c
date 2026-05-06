/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:23:07 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/26 19:08:11 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Dispatch to builtin or external
 * @param argv
 * @param env
 * @return int
 */
int	ft_exec_cmd(char **argv, t_env *env)
{
	int	status;

	if (!argv || !argv[0])
		return (0);
	if (!env)
		return (1);
	status = 1;
	if (ft_is_builtin(argv[0]))
		status = ft_exec_builtin(argv, env);
	else
		status = ft_exec_external(argv, env);
	return (status);
}
