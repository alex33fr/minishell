/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 08:59:01 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:15:22 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_result;
	size_t	s_len;
	size_t	i;
	size_t	s1_len;

	if (!s1 || !s2)
		return (0);
	i = 0;
	s1_len = ft_strlen(s1);
	s_len = s1_len + ft_strlen(s2);
	s_result = malloc(sizeof(char) * s_len + 1);
	if (s_result == 0)
		return (0);
	while (i < s_len)
	{
		if (i < ft_strlen(s1))
			s_result[i] = s1[i];
		else
			s_result[i] = s2[i - s1_len];
		i++;
	}
	s_result[i] = '\0';
	return (s_result);
}
