/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:08:16 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:15:58 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*malloc_slen(size_t len)
{
	char	*s;

	if (len > 0)
	{
		s = malloc(len * sizeof(char) + 1);
		if (s == 0)
			return (0);
		return (s);
	}
	if (len == 0)
	{
		s = malloc(sizeof(char));
		if (s == 0)
			return (0);
		return (s);
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			len_s;
	char			*s_result;

	i = 0;
	if (s == 0)
		return (0);
	len_s = ft_strlen(s);
	if (len > len_s - start)
		len = len_s - start;
	if (start > len_s)
		len = 0;
	s_result = malloc_slen(len);
	if (s_result == 0)
		return (0);
	while (len > 0 && s[start + i])
	{
		s_result[i] = s[start + i];
		i++;
		len--;
	}
	s_result[i] = '\0';
	return (s_result);
}
