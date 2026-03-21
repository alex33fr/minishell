/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:17:30 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:15:11 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	size;
	char	*temp_char;
	char	c1;

	i = 0;
	size = ft_strlen(s);
	temp_char = (char *)s;
	c1 = (char)c;
	while (i <= size)
	{
		if (temp_char[i] == c1)
			return (&temp_char[i]);
		i++;
	}
	return (0);
}
