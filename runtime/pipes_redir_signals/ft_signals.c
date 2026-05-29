/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 08:55:14 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/29 13:27:46 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * SIGINT handler: store signal number, redisplay prompt
 * @order 1.1.2.1
 */
static void	sig_int(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief
 * Setup signals
 * SIGINT -> new prompt line, SIGQUIT -> ignored
 * @order 1.1.2
 */
void	ft_setup_signals(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief
 * Reset signals to default in children.
 * @order 1.2.3.5.3.1.2.1.1.1
 */
void	ft_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief
 * SIGINT handler while parent waits for a child: no readline calls.
 * @order 1.2.3.5.2.1
 */
static void	sig_int_exec(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
}

/**
 * @brief
 * Setup signals while waiting for child: avoids double-prompt from rl_*.
 * @order 1.2.3.5.2
 */
void	ft_setup_signals_exec(void)
{
	signal(SIGINT, sig_int_exec);
	signal(SIGQUIT, SIG_IGN);
}
