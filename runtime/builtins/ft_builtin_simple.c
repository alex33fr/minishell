/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:11:46 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/09 22:44:03 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Print current working directory to stdout
 * @return int
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
 * Print all env variables to stdout
 * @param env
 * @return int
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

/**
 * @brief
 * Exit shell with optional numeric exit code from argv[1]
 * @param argv
 * @return int
 */
int	ft_builtin_exit(char **argv)
{
	int	result;

	result = 0;
	if (!argv[1])
		exit(0);
	if (!ft_isdigit(argv[1][0]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(2);
	}
	result = ft_atoi(argv[1]);
	exit(result);
}

/**
 * @brief
 * Print argv to stdout, handle -n flag to skip newline
 * @param argv
 * @return int
 */
int	ft_builtin_echo(char **argv)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	if (argv[1] && !ft_strcmp(argv[1], "-n"))
	{
		newline = 0;
		i = 2;
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
 * Change current directory and update PWD and OLDPWD in env
 * @param argv
 * @param env
 * @return int
 */
int	ft_builtin_cd(char **argv, t_env *env)
{
	char	buffer[PATH_MAX];
	char	*old_pwd;

	if (!argv[1])
	{
		ft_putstr_fd("cd: missing argument\n", 2);
		return (1);
	}
	old_pwd = ft_env_get(env, "PWD");
	if (chdir(argv[1]) != 0)
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
