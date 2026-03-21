/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:37:20 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:15:54 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	isinset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	size_t			end;
	char			*s_result;

	if (!s1 || !set)
		return (0);
	start = 0;
	end = ft_strlen(s1) - 1;
	s_result = (char *)s1;
	while (isinset(s1[start], set))
		start++;
	while (isinset(s1[end], set))
		end--;
	s_result = ft_substr(s_result, start, end - (size_t)start + 1);
	if (s_result == 0)
		return (0);
	return (s_result);
}
