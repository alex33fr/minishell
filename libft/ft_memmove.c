/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:27:33 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:14:35 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*p_dest;
	const char	*p_src;

	p_dest = dest;
	p_src = src;
	if (!dest && !src && n > 0)
		return (0);
	if (p_dest > p_src)
	{
		p_dest += n - 1;
		p_src += n - 1;
		while (n--)
		{
			*p_dest-- = *p_src--;
		}
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}
