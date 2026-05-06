/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:03:18 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/03 14:11:33 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Return size of env nodes
 * @param env
 * @return int
 */
static int	ft_env_size(t_env *env)
{
	int		i;
	t_env_n	*node;

	if (!env)
		return (0);
	i = 0;
	node = env->head;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

/**
 * @brief
 * join key to = to value
 * @param key
 * @param value
 * @return char*
 */
static char	*ft_env_join_entry(char *key, char *value)
{
	char	*tmp;
	char	*entry;

	if (!key)
		return (NULL);
	if (!value)
	{
		entry = ft_strdup(key);
		return (entry);
	}
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!entry)
		return (NULL);
	return (entry);
}

/**
 * @brief
 * Convert node to char ** for execve, format KEY=value finished by NULL
 * @param env
 * @return char**
 */
char	**ft_env_to_envp(t_env *env)
{
	int		i;
	int		size;
	char	**tab_envp;
	t_env_n	*node;

	if (!env)
		return (NULL);
	size = ft_env_size(env);
	tab_envp = ft_calloc(size + 1, sizeof(char *));
	if (!tab_envp)
		return (NULL);
	i = -1;
	node = env->head;
	while (node)
	{
		tab_envp[++i] = ft_env_join_entry(node->key, node->value);
		if (!tab_envp[i])
		{
			ft_free_tab(tab_envp);
			return (NULL);
		}
		node = node->next;
	}
	tab_envp[++i] = NULL;
	return (tab_envp);
}
