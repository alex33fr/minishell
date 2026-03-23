/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:11:24 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:14:21 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;
	size_t			i;
	unsigned char	c1;

	i = 0;
	c1 = (unsigned char)c;
	temp = (unsigned char *)s;
	while (i < n)
	{
		if (temp[i] == c1)
			return (&temp[i]);
		i++;
	}
	return (0);
}
