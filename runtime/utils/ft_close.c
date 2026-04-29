/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:47:33 by aprivalo          #+#    #+#             */
/*   Updated: 2026/03/31 16:32:10 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  Close fd in_1 and in_2 only if > 2 to protect stdin/stdout/stderr.
 * @order  U.4 - utility called throughout the runtime wherever fds are managed
 * @param  in_1 first fd to close (-1 or 0-2 = skip)
 * @param  in_2 second fd to close (-1 or 0-2 = skip)
 */
void	ft_close(int in_1, int in_2)
{
	if (in_1 > 2)
		close(in_1);
	if (in_2 > 2)
		close(in_2);
}
