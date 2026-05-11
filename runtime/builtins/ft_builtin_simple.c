/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_simple.c                                :+:      :+:    :+:   */
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

	if (getcwd(buffer, PATH_MAX))
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
	env->exit_flag = 1;
	env->exit_code = code;
	return (code);
}

/**
 * @brief
 * Print "exit: arg: numeric argument required" to stderr, free arg, return 2.
 * @order 1.2.3.5.2.2.2.7.2
 */
static int	ft_exit_err(t_env *env, char *arg)
{
	int	code;

	code = 0;
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free(arg);
	code = ft_exit_set(env, 2);
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
	int		err;

	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "--"))
		return (ft_exit_set(env, env->exit_code));
	arg = ft_strtrim(cmd->args[1], " \t");
	if (!arg || !ft_is_valid_num(arg))
		return (ft_exit_err(env, arg));
	if (cmd->args[2])
	{
		free(arg);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	err = 0;
	val = ft_exit_atol(arg, &err);
	if (err)
	{
		ft_exit_err(env, arg);
		return (2);
	}
	free(arg);
	return (ft_exit_set(env, (unsigned char)val));
}

/**
 * @brief
 * Print argv words separated by spaces, with newline unless -n flag is set.
 * @order 1.2.3.5.2.2.2.1
 */
int	ft_builtin_echo(char **argv)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (argv[i] && ft_is_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		if (write(1, argv[i], ft_strlen(argv[i])) == -1)
			return (perror("echo: write error"), 1);
		if (argv[i + 1] && write(1, " ", 1) == -1)
			return (perror("echo: write error"), 1);
		i++;
	}
	if (newline && write(1, "\n", 1) == -1)
	{
		perror("echo: write error");
		return (1);
	}
	return (0);
}
