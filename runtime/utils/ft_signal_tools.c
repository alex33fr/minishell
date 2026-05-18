/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:18:06 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/18 12:11:19 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * SIGINT handler during heredoc input: store signal, print ^C and newline.
 * Manual write because ECHOCTL is disabled during heredoc reading.
 * @order 1.2.3.5.2.1.4.1.2
 */
void	sig_int_heredoc(int sig)
{
	g_signal = sig;
	write(1, "^C", 2);
	write(1, "\n", 1);
}
