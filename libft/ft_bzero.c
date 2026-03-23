/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:06:32 by byonis            #+#    #+#             */
/*   Updated: 2026/03/23 10:09:54 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*temp;
	size_t	i;

	temp = s;
	i = 0;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
	s = temp;
}
