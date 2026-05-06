/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:12:43 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/27 12:13:30 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param env 
 * @param key 
 * @param sep 
 */
static void	ft_do_append(t_env *env, char *key, char *sep)
{
	char	*old;
	char	*new;

	old = ft_env_get(env, key);
	if (!old)
		old = "";
	new = ft_strjoin(old, sep + 1);
	ft_env_set(env, key, new);
	free(new);
}

/**
 * @brief 
 * 
 * @param arg 
 * @param sep 
 * @param env 
 * @return int 
 */
static int	ft_export_sep(char *arg, char *sep, t_env *env)
{
	int		append;
	char	*key;

	append = (sep > arg && *(sep - 1) == '+');
	key = ft_substr(arg, 0, sep - arg - append);
	if (!key || !ft_is_valid_name(key))
	{
		free(key);
		return (1);
	}
	if (append)
		ft_do_append(env, key, sep);
	else
		ft_env_set(env, key, sep + 1);
	free(key);
	return (0);
}

/**
 * @brief 
 * 
 * @param argv 
 * @param env 
 * @return int 
 */
int	ft_builtin_export(char **argv, t_env *env)
{
	char	*sep;
	int		i;
	int		status;
	int		ret;

	if (!argv[1])
	{
		ret = ft_builtin_env(env);
		return (ret);
	}
	i = 1;
	status = 0;
	while (argv[i])
	{
		sep = ft_strchr(argv[i], '=');
		if (sep && ft_export_sep(argv[i], sep, env))
			status = ft_export_err(argv[i]);
		else if (!sep && !ft_is_valid_name(argv[i]))
			status = ft_export_err(argv[i]);
		i++;
	}
	return (status);
}

/**
 * @brief 
 * 
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
