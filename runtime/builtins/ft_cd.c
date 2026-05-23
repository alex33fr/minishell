/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:22:10 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/23 11:10:20 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Update OLDPWD and PWD in env; print error to stderr if getcwd fails.
 * @order 1.2.3.5.2.2.2.2.1
 */
static void	ft_cd_update_pwd(t_env *env, char *old_pwd, char *buffer)
{
	char	*cwd;

	if (!old_pwd)
		return ;
	cwd = getcwd(buffer, PATH_MAX);
	if (!cwd)
	{
		ft_err_2();
		return ;
	}
	ft_env_set(env, "OLDPWD", old_pwd);
	ft_env_set(env, "PWD", buffer);
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
	int		status;

	if (argv[1] && argv[2])
		return (ft_error5());
	if (argv[1] && !argv[1][0])
		return (0);
	old_pwd = ft_env_get(env, "PWD");
	target = ft_cd_target(argv, env);
	if (!target)
		return (1);
	if (!target[0])
		return (0);
	status = chdir(target);
	if (status != 0)
	{
		ft_err_4(target);
		return (1);
	}
	ft_cd_update_pwd(env, old_pwd, buffer);
	return (0);
}
