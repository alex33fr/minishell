/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:56:47 by aprivalo          #+#    #+#             */
/*   Updated: 2026/03/23 10:08:00 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static unsigned int	ft_int_len(unsigned int n)
{
	unsigned int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static unsigned int	ft_init(unsigned long *nb, char **tab_itoa)
{
	if (*nb == 0)
	{
		*tab_itoa = ft_calloc(2, sizeof(char));
		if (!*tab_itoa)
			return (-1);
		(*tab_itoa)[0] = '0';
		return (1);
	}
	return (0);
}

static char	*ft_itoa_uns(unsigned int n)
{
	char			*tab_itoa;
	unsigned long	len;
	unsigned long	nb;
	unsigned long	state;

	nb = (unsigned long)n;
	state = ft_init(&nb, &tab_itoa);
	if (state == 1)
		return (tab_itoa);
	len = ft_int_len(n);
	tab_itoa = ft_calloc(len + 1, sizeof(char));
	if (!tab_itoa)
		return (NULL);
	while (nb > 0)
	{
		tab_itoa[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (tab_itoa);
}

int	ft_print_dec(va_list args)
{
	unsigned int	asc;
	unsigned int	len;
	char			*str;

	asc = va_arg(args, unsigned int);
	str = ft_itoa_uns(asc);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
