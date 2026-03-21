/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:35:02 by byonis            #+#    #+#             */
/*   Updated: 2026/01/01 12:53:49 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_strlen_szt(const char *s)
{
	size_t	n;

	n = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[n])
		n++;
	return (n);
}

char	*ft_strjoin_m(char *s1, char *s2)
{
	char	*s_result;
	size_t	s_len;
	size_t	i;
	size_t	s1_len;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	s1_len = ft_strlen_szt(s1);
	s_len = s1_len + ft_strlen_szt(s2);
	s_result = malloc(sizeof(char) * (s_len + 1));
	if (s_result == NULL)
		return (NULL);
	while (i < s_len)
	{
		if (i < s1_len)
			s_result[i] = s1[i];
		else
			s_result[i] = s2[i - s1_len];
		i++;
	}
	free(s1);
	free(s2);
	s_result[i] = '\0';
	return (s_result);
}

char	*ft_substr_m(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			len_s;
	char			*s_result;

	i = 0;
	if (s == 0)
		return (0);
	len_s = ft_strlen_szt(s);
	if (len > len_s - start)
		len = len_s - start;
	if (start > len_s)
		len = 0;
	s_result = malloc((len + 1) * sizeof(char));
	if (s_result == 0)
		free(s);
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
