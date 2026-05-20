/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors2.c                                       :+:      :+:    :+:   */
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
 * Print "exit: arg: numeric argument required" to stderr, free arg, return 2.
 * @order 1.2.3.5.2.2.2.7.2
 */
int	ft_exit_err(t_env *env, char *arg)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free(arg);
	env->exit_flag = 1;
	env->exit_code = 2;
	return (2);
}
