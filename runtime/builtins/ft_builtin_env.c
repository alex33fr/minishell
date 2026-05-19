/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:12:43 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/19 14:01:10 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Append the value after sep[1] to the existing env entry for key.
 * @order 1.2.3.5.2.2.2.4.1.2
 */
static void	ft_do_join(t_env *env, char *key, char *sep)
{
	char	*old;
	char	*new;

	old = ft_env_get(env, key);
	if (!old)
		old = "";
	new = ft_strjoin(old, sep + 1);
	if (!new)
		return ;
	ft_env_set(env, key, new);
	free(new);
}

/**
 * @brief
 * Handle "KEY=val" or "KEY+=val" export: set or join value in env.
 * @order 1.2.3.5.2.2.2.4.1
 */
static int	ft_export_sep(char *arg, char *sep, t_env *env)
{
	int		join;
	char	*key;

	join = (sep > arg && *(sep - 1) == '+');
	key = ft_substr(arg, 0, sep - arg - join);
	if (!key || !ft_is_valid_name(key))
	{
		free(key);
		return (1);
	}
	if (join)
		ft_do_join(env, key, sep);
	else
		ft_env_set(env, key, sep + 1);
	free(key);
	return (0);
}

/**
 * @brief
 * Export variables from argv into env; print env if no args given.
 * @order 1.2.3.5.2.2.2.4
 */
int	ft_builtin_export(char **argv, t_env *env)
{
	char	*sep;
	int		i;
	int		status;
	int		sort;

	if (!argv[1])
	{
		sort = ft_export_print_sorted(env);
		return (sort);
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
		else if (!sep)
			status = ft_export_no_value(argv[i], env);
		i++;
	}
	return (status);
}

/**
 * @brief
 * Remove each argv key from env.
 * @order 1.2.3.5.2.2.2.5
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

/**
 * @brief
 * Print all env entries as "KEY=value" lines to stdout.
 * @order 1.2.3.5.2.2.2.6
 */
int	ft_builtin_env(t_env *env)
{
	char	**envp;
	int		i;

	envp = ft_env_to_envp(env);
	if (!envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	ft_free_tab(envp);
	return (0);
}
