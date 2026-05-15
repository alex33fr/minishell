/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:18:06 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/15 13:21:34 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * Quit CTRL + \
 * @param sig 
 */
void	sig_int_heredoc(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
}