/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:28:44 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/06 11:50:11 by aprivalo         ###   ########.fr       */
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

	if (ft_strcmp(exec->argv[0], ".") == 0)
	{
		ft_putstr_fd(".: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		ft_child_free(exec);
		exit(2);
	}
	path = ft_find_path(exec->argv[0], exec->env);
	if (!path)
	{
		ft_err_3(exec->argv[0], ft_is_path_cmd(exec->argv[0]));
		ft_child_free(exec);
		exit(127);
	}
	return (path);
}

/**
 * @brief
 * Call execve with path and argv from exec.
 * If execve fails:
 *   - argv[0] is empty string (from "" or '' input): print bash-style
 *     "Command '' not found" instead of perror to avoid "Permission denied",
 *     which occurs because ft_find_path("") resolves to a PATH directory
 *     (access(dir, X_OK)==0) and execve on a directory returns EACCES.
 *   - otherwise: perror(argv[0]) for the actual error.
 * Exit 126 if file exists but not executable, 127 if not found.
 * @order 1.2.3.5.2.2.3.1.2
 */
void	ft_exec_child(t_exec *exec, char *path)
{
	struct stat	st;
	int			code;
	int			status;
	int			is_path;

	execve(path, exec->argv, exec->envp);
	if (exec->argv[0][0] == '\0')
		ft_putstr_fd("Command '' not found =)\n", 2);
	else
		perror(exec->argv[0]);
	status = stat(path, &st);
	if (status != 0)
	{
		free(path);
		ft_child_free(exec);
	}
	is_path = (ft_strchr(exec->argv[0], '/') != NULL);
	code = ft_exit_code(&st, is_path);
	free(path);
	ft_child_free(exec);
	exit(code);
}
