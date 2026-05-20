/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:32:30 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/07 14:10:30 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Return 1 if s is an optional sign followed by one or more digits, else 0.
 * @order 1.2.3.5.2.2.2.7.1
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
 * Convert s to long; set *overflow to 1 and return 0 if out of range.
 * @order 1.2.3.5.2.2.2.7.3
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
 * Return 1 if s is a valid env identifier (alnum/underscore, no leading digit).
 * @order 1.2.3.5.2.2.2.4.1.1
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
 * Return 1 if s matches echo's -n flag format ("-n", "-nn", etc.), else 0.
 * @order 1.2.3.5.2.2.2.1.1
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

/**
 * @brief
 * Resolve cd target: HOME if no arg or "--", else argv[1].
 * @order 1.2.3.5.2.2.2.2.2
 */
char	*ft_cd_target(char **argv, t_env *env)
{
	if (!argv[1] || !ft_strcmp(argv[1], "--"))
	{
		if (!ft_env_get(env, "HOME"))
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
		return (ft_env_get(env, "HOME"));
	}
	return (argv[1]);
}
