/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:03:30 by byonis            #+#    #+#             */
/*   Updated: 2025/12/29 15:13:34 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	n_size_str(long int n)
{
	int	cpt;

	cpt = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		cpt++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		cpt++;
	}
	return (cpt);
}

int	ft_pow(unsigned int x, unsigned int n)
{
	if (n < 0)
		return (0);
	if (n == 0)
		return (1);
	return (x * ft_pow(x, n - 1));
}

char	*ft_itoa_pos(int n)
{
	char	*s;
	int		size;
	int		i;

	i = 0;
	size = n_size_str(n);
	s = malloc((size + 1) * sizeof(char));
	if (s == 0)
		return (0);
	while (i < size)
	{
		s[i] = (n / ft_pow(10, size - i -1)) + '0';
		n -= ((s[i] - 48) * ft_pow(10, size - i - 1));
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_itoa_neg(int n)
{
	char		*s;
	int			size;
	int			i;
	long int	nb;

	nb = (long int)n;
	size = n_size_str(nb);
	s = malloc((size + 1) * sizeof(char));
	if (s == 0)
		return (0);
	i = size;
	nb *= -1;
	while (i > 0)
	{
		i--;
		s[i] = nb % 10 + '0';
		nb /= 10;
	}
	s[size] = '\0';
	s[0] = '-';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s_result;

	if (n >= 0)
	{
		s_result = ft_itoa_pos(n);
		if (s_result == 0)
			return (0);
		return (s_result);
	}
	s_result = ft_itoa_neg(n);
	if (s_result == 0)
		return (0);
	return (s_result);
}
