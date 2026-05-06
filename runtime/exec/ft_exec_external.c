/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:41:06 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/08 16:10:24 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Run in child process: resolve path then execve
 * @param exec
 * @param envp
 */
static void	ft_run_process(t_exec *exec, char **envp)
{
	char	*path;

	path = ft_resolve_path(exec);
	ft_exec_child(exec, path, envp);
}

/**
 * @brief
 * Fork and execute an external command from argv using env
 * Return exit code of the child process
 * @param argv
 * @param env
 * @return int
 */
int	ft_exec_external(char **argv, t_env *env)
{
	t_exec	exec;
	char	**envp;
	pid_t	pid;
	int		ret;

	if (!argv || !argv[0] || !env)
		return (1);
	exec.argv = argv;
	exec.env = env;
	envp = ft_env_to_envp(env);
	if (!envp)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		ft_free_tab(envp);
		return (1);
	}
	if (pid == 0)
		ft_run_process(&exec, envp);
	ft_free_tab(envp);
	ret = ft_wait_child(pid);
	return (ret);
}
