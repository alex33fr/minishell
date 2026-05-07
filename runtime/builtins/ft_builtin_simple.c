/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:11:46 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/07 08:05:12 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Print the current working directory to stdout. Return 1 on getcwd failure.
 * @order 1.2.3.5.2.2.2.3
 */
int	ft_builtin_pwd(void)
{
	char	buffer[PATH_MAX];

	if (!getcwd(buffer, PATH_MAX))
	{
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(buffer, 1);
	ft_putstr_fd("\n", 1);
	return (0);
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
 * Validate exit code arg, set exit flag, return status.
 * @order 1.2.3.5.2.2.2.7
 */
int	ft_builtin_exit(t_cmd *cmd, t_env *env)
{
	long	val;
	int		err;

	if (!cmd->args[1])
		return (ft_exit_set(env, 0));
	if (!ft_is_valid_num(cmd->args[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (ft_exit_set(env, 2));
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	err = 0;
	val = ft_exit_atol(cmd->args[1], &err);
	if (err)
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (ft_exit_set(env, 2));
	}
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
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}

/**
 * @brief
 * Change directory to argv[1], update PWD and OLDPWD in env.
 * @order 1.2.3.5.2.2.2.2
 */
int	ft_builtin_cd(char **argv, t_env *env)
{
	char	buffer[PATH_MAX];
	char	*old_pwd;
	char	*target;

	if (!argv[1])
	{
		ft_putstr_fd("cd: missing argument\n", 2);
		return (1);
	}
	old_pwd = ft_env_get(env, "PWD");
	target = ft_cd_target(argv, env);
	if (!target)
		return (1);
	if (chdir(target) != 0)
	{
		perror("cd");
		return (1);
	}
	ft_env_set(env, "OLDPWD", old_pwd);
	if (!getcwd(buffer, PATH_MAX))
		return (1);
	ft_env_set(env, "PWD", buffer);
	return (0);
}
