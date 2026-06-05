/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:18:06 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/23 11:37:07 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * SIGINT handler during heredoc input: store signal number, write "^C".
 * No newline here: ft_heredoc_getc returns '\n' so readline echoes it,
 * avoiding a spurious blank line after ^C.
 * ECHOCTL is disabled so the terminal does not echo "^C" on its own.
 * @order 1.2.3.5.2.1.4.1.2
 */
void	sig_int_heredoc(int sig)
{
	g_signal = sig;
	write(1, "^C", 2);
}

/**
 * @brief
 * Custom rl_getc_function used during heredoc reading.
 * Replaces readline's default character reader so we control EINTR handling:
 *   - if g_signal is set (SIGINT arrived), return '\n' so readline closes
 *     the current line cleanly and returns "", which ft_heredoc_check catches.
 *   - if read() is interrupted (EINTR) without a signal, retry.
 *   - on any other error or EOF, return EOF to stop readline.
 * stream is ignored: we always read from STDIN_FILENO directly.
 * rl_catch_signals must be 0 when this is active so readline does not
 * reinstall its own SIGINT handler and override ours.
 * @order 1.2.3.5.2.1.4.1.2.1
 */
int	ft_heredoc_getc(FILE *stream)
{
	unsigned char	c;
	int				ret;

	(void)stream;
	while (1)
	{
		if (g_signal)
			return ('\n');
		ret = read(STDIN_FILENO, &c, 1);
		if (ret == 1)
			return ((int)c);
		if (errno == EINTR && !g_signal)
			continue ;
		return (EOF);
	}
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
