/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:55:52 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:15:42 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s0;
	unsigned char	*s;

	i = 0;
	s0 = (unsigned char *)s1;
	s = (unsigned char *)s2;
	while ((i < n) && (s0[i] || s[i]))
	{
		if (s0[i] != s[i])
			return (s0[i] - s[i]);
		i++;
	}
	return (0);
}
