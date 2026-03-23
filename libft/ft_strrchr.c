/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:11:46 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:15:50 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	long	i;
	char	*temp;
	char	c1;

	if (s == 0)
		return (0);
	i = (long)ft_strlen(s);
	temp = (char *)s;
	c1 = (char)c;
	while (i >= 0)
	{
		if (temp[i] == c1)
			return (&temp[i]);
		i--;
	}
	return (0);
}
