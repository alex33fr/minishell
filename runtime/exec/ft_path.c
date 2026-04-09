/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:35:19 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/08 15:59:47 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Split PATH from env
 * Return NULL if PATH not exist
 * @param env
 * @return char**
 */
static char	**ft_get_path_splitted(t_env *env)
{
	char	*path_val;
	char	**paths;

	path_val = ft_env_get(env, "PATH");
	if (!path_val)
		return (NULL);
	paths = ft_split(path_val, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

/**
 * @brief
 * Search cmd in each directory of paths
 * Return full path if found or NULL
 * @param paths
 * @param cmd
 * @return char*
 */
static char	*ft_search_path(char **paths, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	if (!paths || !cmd)
		return (NULL);
	while (paths[i])
	{
		path = ft_join_cmd_path(paths[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

/**
 * @brief
 * Return 1 if cmd contains '/'
 * @param cmd
 * @return int
 */
int	ft_is_path_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '/'))
		return (1);
	return (0);
}

/**
 * @brief
 * Join dir and cmd with '/' separator
 * Return string "dir/cmd", or NULL on fail
 * @param dir
 * @param cmd
 * @return char*
 */
char	*ft_join_cmd_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	if (!dir || !cmd)
		return (NULL);
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

/**
 * @brief
 * Resolve the full path of cmd using the env linked list
 * If cmd contains '/', checks it directly
 * @param cmd
 * @param env
 * @return char*
 */
char	*ft_find_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path;

	if (!cmd || !env)
		return (NULL);
	if (ft_is_path_cmd(cmd))
	{
		path = NULL;
		if (access(cmd, X_OK) == 0)
			path = ft_strdup(cmd);
		return (path);
	}
	paths = ft_get_path_splitted(env);
	if (!paths)
		return (NULL);
	path = ft_search_path(paths, cmd);
	ft_free_tab(paths);
	return (path);
}
