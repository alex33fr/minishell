/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:18:06 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/06 19:04:45 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * SIGINT handler during heredoc input: store the signal number, print a
 * newline, then close stdin so readline's blocked read fails and returns
 * NULL, which breaks the heredoc loop cleanly (no rl_getc_function needed).
 * @order 1.2.3.5.2.1.4.1.2
 */
void	sig_int_heredoc(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

/**
 * @brief
 * Setup signals for heredoc input: SIGINT closes stdin to unblock readline.
 * @order 1.2.3.5.2.1.4.1.2
 */
void	ft_setup_signals_heredoc(void)
{
	signal(SIGINT, sig_int_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief
 * Translate last raw exit status to 130 if SIGINT was caught, else keep it.
 * Resets g_signal to 0 after consuming the SIGINT.
 * @order 1.2.3.5.2.1
 */
int	ft_handle_signal(int last_status)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		return (130);
	}
	return (last_status);
}
