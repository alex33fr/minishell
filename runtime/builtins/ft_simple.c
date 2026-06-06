/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:11:46 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/11 21:04:08 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Print the current working directory to stdout. Return 1 on getcwd failure.
 * @order 1.2.3.5.2.2.2.3
 */
int	ft_builtin_pwd(t_env *env)
{
	char	buffer[PATH_MAX];
	char	*cached;

	cached = getcwd(buffer, PATH_MAX);
	if (cached)
	{
		ft_putstr_fd(buffer, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	cached = ft_env_get(env, "PWD");
	if (cached)
	{
		ft_putstr_fd(cached, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	perror("pwd");
	return (1);
}

/**
 * @brief
 * Set exit_flag and exit_code in env, return code.
 * @order 1.2.3.5.2.2.2.7.1
 */
static int	ft_exit_set(t_env *env, int code)
{
	int	is_tty;
	int	is_main;

	is_tty = isatty(STDIN_FILENO);
	is_main = (env->in_child == 0);
	if (is_tty && is_main)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	env->exit_flag = 1;
	env->exit_code = code;
	return (code);
}

/**
 * @brief
 * Validate exit code arg, set exit flag, return status.
 * @order 1.2.3.5.2.2.2.7
 */
int	ft_builtin_exit(t_cmd *cmd, t_env *env)
{
	char	*arg;
	long	val;
	int		ret;
	int		valid;

	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "--"))
	{
		ret = ft_exit_set(env, env->exit_code);
		return (ret);
	}
	arg = ft_strtrim(cmd->args[1], " \t");
	valid = arg && ft_is_valid_num(arg);
	if (!valid)
	{
		ret = ft_exit_err(env, arg);
		return (ret);
	}
	ret = ft_exit_parse_arg(env, cmd->args, arg, &val);
	if (ret)
		return (ret);
	free(arg);
	ret = ft_exit_set(env, (unsigned char)val);
	return (ret);
}
