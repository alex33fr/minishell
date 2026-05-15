/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:18:06 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/15 15:09:59 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * SIGINT handler during heredoc input: store signal number and newline.
 * @order 1.2.3.5.2.1.4.1.2
 */
void	sig_int_heredoc(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
}
