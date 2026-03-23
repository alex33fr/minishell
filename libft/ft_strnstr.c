/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:30:32 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:15:46 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	stop;

	i = 0;
	j = 0;
	if (!little[i])
		return ((char *)big);
	while (i < len && big[i])
	{
		stop = i;
		while ((char)big[i + j] == (char)little[j] && stop != len)
		{
			if ((char)little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
			stop++;
		}
		j = 0;
		i++;
	}
	return (0);
}
