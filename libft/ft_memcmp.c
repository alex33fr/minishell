/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:08:48 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:14:26 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_0;
	unsigned char	*s2_0;

	i = 0;
	s1_0 = (unsigned char *)s1;
	s2_0 = (unsigned char *)s2;
	while (i < n)
	{
		if (s1_0[i] != s2_0[i])
			return (s1_0[i] - s2_0[i]);
		i++;
	}
	return (0);
}
