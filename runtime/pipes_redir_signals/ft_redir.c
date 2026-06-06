/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 09:41:07 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/06 22:38:11 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Read one heredoc line via readline (supports line editing).
 * Return NULL on EOF.
 * Caller must free the result.
 * @order 1.2.1 / 1.2.3.5.2.1.4.1.1
 */
char	*ft_read_heredoc_line(void)
{
	char	*line;
	char	*res;

	line = readline("> ");
	if (!line)
		return (NULL);
	res = ft_strdup(line);
	free(line);
	return (res);
}
