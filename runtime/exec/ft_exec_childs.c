/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_childs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:28:44 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/08 16:02:23 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Resolve full path of argv[0]
 * Print error and exit 127 if not found
 * @param exec
 * @return char*
 */
char	*ft_resolve_path(t_exec *exec)
{
	char	*path;

	path = ft_find_path(exec->argv[0], exec->env);
	if (!path)
	{
		ft_putstr_fd(exec->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return (path);
}

/**
 * @brief
 * Call execve with path and argv from exec
 * Exit 126 if file exists but not executable
 * Exit 127 if not found
 * @param exec
 * @param path
 * @param envp
 */
void	ft_exec_child(t_exec *exec, char *path, char **envp)
{
	execve(path, exec->argv, envp);
	perror(exec->argv[0]);
	free(path);
	if (access(exec->argv[0], F_OK) == 0)
		exit(126);
	exit(127);
}

