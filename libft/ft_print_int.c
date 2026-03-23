/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:32:55 by aprivalo          #+#    #+#             */
/*   Updated: 2026/03/23 10:08:06 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_print_int(va_list args)
{
	int		asc;
	int		len;
	char	*str;

	asc = va_arg(args, int);
	str = ft_itoa(asc);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
