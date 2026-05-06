/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:32:30 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/27 11:31:17 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
int	ft_is_valid_num(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief 
 * 
 * @param s 
 * @param overflow 
 * @return long 
 */
long	ft_exit_atol(char *s, int *overflow)
{
	unsigned long	result;
	unsigned long	limit;
	int				sign;
	int				i;

	*overflow = 0;
	result = 0;
	sign = 1 - 2 * (s[0] == '-');
	i = (s[0] == '+' || s[0] == '-');
	while (s[i])
	{
		limit = ((unsigned long)LONG_MAX + (sign == -1) - (s[i] - '0')) / 10;
		if (result > limit)
		{
			*overflow = 1;
			return (0);
		}
		result = result * 10 + (s[i] - '0');
		i++;
	}
	if (sign == -1)
		return (-(long)(result - 1) - 1);
	return ((long)result);
}

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
int	ft_is_valid_name(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (ft_isdigit(s[0]))
		return (0);
	while (s[i])
	{
		if (s[i] != '_' && !ft_isalnum(s[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
int	ft_is_n_flag(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (s[i] != '-')
		return (0);
	i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
