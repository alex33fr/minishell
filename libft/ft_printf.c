/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:49:22 by aprivalo          #+#    #+#             */
/*   Updated: 2026/03/23 10:09:37 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	int	ft_type_args(char type, va_list args)
{
	int	len;

	len = 0;
	if (type == 'c')
		len = ft_print_char(args);
	else if (type == 's')
		len = ft_print_string(args);
	else if (type == 'd' || type == 'i')
		len = ft_print_int (args);
	else if (type == 'p')
		len = ft_print_ptr(args);
	else if (type == 'u')
		len = ft_print_dec(args);
	else if (type == 'x')
		len = ft_print_hex_lo(args);
	else if (type == 'X')
		len = ft_print_hex_up(args);
	else if (type == '%')
		len = ft_print_percent(args);
	return (len);
}

static int	ft_define_format(const char *s, va_list args)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			i += ft_type_args(*(s + 1), args);
			s += 2;
		}
		else
		{
			write(1, s, 1);
			i++;
			s++;
		}
	}
	return (i);
}

int	ft_printf(const char *s, ...)
{
	int		len;
	va_list	args;

	if (!s)
		return (0);
	va_start(args, s);
	len = ft_define_format(s, args);
	va_end(args);
	return (len);
}
