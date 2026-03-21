/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:05:29 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:15:39 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	size;
	char	*s_result;

	if (!s || !f)
		return (0);
	size = ft_strlen(s);
	i = 0;
	s_result = malloc((size + 1) * sizeof(char));
	if (!s_result)
		return (0);
	while (i < size)
	{
		s_result[i] = f(i, s[i]);
		i++;
	}
	s_result[i] = '\0';
	return (s_result);
}
