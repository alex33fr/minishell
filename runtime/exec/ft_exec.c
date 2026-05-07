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
 * Dispatch argv[0] to builtin or external, return its exit status.
 * @order 1.2.3.5.2.2
 */
int	ft_exec_cmd(char **argv, t_shell *shell)
{
	int	status;

	if (!argv || !argv[0])
		return (0);
	if (!shell || !shell->env)
		return (1);
	status = 1;
	if (ft_is_builtin(argv[0]))
		status = ft_exec_builtin(argv, shell);
	else
		status = ft_exec_external(argv, shell->env);
	return (status);
}
