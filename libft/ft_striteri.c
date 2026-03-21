/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:27:27 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:15:19 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;
	size_t	size;

	i = 0;
	if (s)
	{
		size = ft_strlen(s);
		while (f && i < size)
		{
			f(i, &s[i]);
			i++;
		}
	}
}
