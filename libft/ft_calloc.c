/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:06:56 by byonis            #+#    #+#             */
/*   Updated: 2026/03/23 10:09:56 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*t;

	if (size != 0 && (nmemb * size) / size != nmemb)
		return (0);
	t = malloc(nmemb * size);
	if (t == 0)
		return (0);
	ft_bzero(t, nmemb * size);
	return (t);
}
