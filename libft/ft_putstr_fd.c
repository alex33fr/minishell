/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:52:19 by byonis            #+#    #+#             */
/*   Updated: 2026/04/01 13:41:25 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	size_t	size;

	i = 0;
	if (fd > -1 && s)
	{
		size = ft_strlen(s);
		while (i < size)
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}
