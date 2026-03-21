/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 08:33:30 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:12:47 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	is_negative;
	int	result;

	i = 0;
	is_negative = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if ((char)nptr[i] == '-' || (char)nptr[i] == '+')
	{
		if (nptr[i] == '-')
			is_negative *= -1;
		i++;
	}
	while ((char)nptr[i] >= '0' && (char)nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	result *= is_negative;
	return (result);
}
