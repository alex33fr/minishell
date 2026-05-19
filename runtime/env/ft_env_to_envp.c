/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:03:18 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/19 14:16:06 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Return size of env nodes
 * @param env
 * @return int
 * @order 1.2.3.2.1
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
		if (node->value)
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
 * @order 1.2.3.2.2
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
		if (!entry)
			return (NULL);
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
 * Fill tab_envp with KEY=value entries, skip nodes without value.
 * @order 1.2.3.2.3
 */
static int	ft_process_envp(char **tab_envp, t_env *env)
{
	t_env_n	*node;
	int		i;

	i = -1;
	node = env->head;
	while (node)
	{
		if (node->value)
		{
			tab_envp[++i] = ft_env_join_entry(node->key, node->value);
			if (!tab_envp[i])
				return (1);
		}
		node = node->next;
	}
	tab_envp[++i] = NULL;
	return (0);
}

/**
 * @brief
 * Convert node to char ** for execve, format KEY=value finished by NULL
 * @param env
 * @return char**
 * @order 1.2.3.2
 */
char	**ft_env_to_envp(t_env *env)
{
	int		size;
	char	**tab_envp;

	if (!env)
		return (NULL);
	size = ft_env_size(env);
	tab_envp = ft_calloc(size + 1, sizeof(char *));
	if (!tab_envp)
		return (NULL);
	if (ft_process_envp(tab_envp, env))
	{
		ft_free_tab(tab_envp);
		return (NULL);
	}
	return (tab_envp);
}
