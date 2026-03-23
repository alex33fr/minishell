/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:22:00 by aprivalo          #+#    #+#             */
/*   Updated: 2026/03/23 10:08:11 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_hex_ptr(unsigned long addr)
{
	char	buffer[32];
	int		i;
	int		result;

	if (addr == 0)
		return (write(1, "0", 1));
	i = 0;
	while (addr)
	{
		buffer[i] = BASE_HEX[addr % 16];
		addr /= 16;
		i++;
	}
	result = i;
	while (i--)
		write(1, &buffer[i], 1);
	return (result);
}

int	ft_print_ptr(va_list args)
{
	unsigned long	addr;
	int				len;

	addr = (unsigned long)va_arg(args, unsigned long);
	if (addr == 0)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	len = ft_hex_ptr((unsigned long)addr);
	return (len + 2);
}
