/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_up.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:22:58 by aprivalo          #+#    #+#             */
/*   Updated: 2026/03/23 10:08:04 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static unsigned int	ft_hex_calc(unsigned int nb)
{
	unsigned int	i;

	i = 0;
	if (nb > 15)
	{
		i += ft_hex_calc(nb / 16);
		i += ft_hex_calc(nb % 16);
	}
	else
	{
		ft_putchar_fd(BASE_HEX_UP[nb], 1);
		i++;
	}
	return (i);
}

int	ft_print_hex_up(va_list args)
{
	unsigned int	len;
	unsigned int	nb;

	len = 0;
	nb = va_arg(args, unsigned int);
	len = ft_hex_calc(nb);
	return (len);
}
