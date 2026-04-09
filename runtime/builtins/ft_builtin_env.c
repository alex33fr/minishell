/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:12:43 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/09 17:17:08 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Add or update a variable in env from "KEY=value" or "KEY"
 * If no argument, display env like builtin env
 * @param argv
 * @param env
 * @return int
 */
int	ft_builtin_export(char **argv, t_env *env)
{
	char	*sep;
	int		i;

	if (!argv[1])
		return (ft_builtin_env(env));
	i = 1;
	while (argv[i])
	{
		sep = ft_strchr(argv[i], '=');
		if (sep)
		{
			*sep = '\0';
			ft_env_set(env, argv[i], sep + 1);
			*sep = '=';
		}
		else
			ft_env_set(env, argv[i], NULL);
		i++;
	}
	return (0);
}

/**
 * @brief
 * Remove one or more variables from env
 * @param argv
 * @param env
 * @return int
 */
int	ft_builtin_unset(char **argv, t_env *env)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		ft_env_unset(env, argv[i]);
		i++;
	}
	return (0);
}
