/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_childs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:28:44 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/07 08:05:12 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Free child-owned resources before exit: envp, env, close saved fds.
 * @order 1.2.3.5.2.2.3.0
 */
static void	ft_child_free(t_exec *exec)
{
	t_cmd	*head;

	ft_close(exec->cmd->saved_in, exec->cmd->saved_out);
	free(exec->pids);
	ft_free_tab(exec->envp);
	head = exec->cmd;
	while (head->prev)
		head = head->prev;
	free_cmds(head);
	ft_env_clear(exec->env);
}

/**
 * @brief
 * Return exit code after execve fails: 126 if not dir or is path, else 127.
 * @order 1.2.3.5.2.2.3.1.2.1
 */
static int	ft_exit_code(struct stat *st, int is_path)
{
	if (!S_ISDIR(st->st_mode))
		return (126);
	if (is_path)
		return (126);
	return (127);
}

/**
 * @brief
 * Resolve full path of argv[0].
 * Print error and exit 127 if not found.
 * @order 1.2.3.5.2.2.3.1.1
 */
char	*ft_resolve_path(t_exec *exec)
{
	char	*path;

	path = ft_find_path(exec->argv[0], exec->env);
	if (!path)
	{
		ft_putstr_fd(exec->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_child_free(exec);
		exit(127);
	}
	return (path);
}

/**
 * @brief
 * Call execve with path and argv from exec.
 * Exit 126 if file exists but not executable, 127 if not found.
 * @order 1.2.3.5.2.2.3.1.2
 */
void	ft_exec_child(t_exec *exec, char *path)
{
	struct stat	st;
	int			code;

	execve(path, exec->argv, exec->envp);
	perror(exec->argv[0]);
	if (stat(path, &st) != 0)
	{
		free(path);
		ft_child_free(exec);
		exit(127);
	}
	code = ft_exit_code(&st, ft_strchr(exec->argv[0], '/') != NULL);
	free(path);
	ft_child_free(exec);
	exit(code);
}
