/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:47:23 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/03 15:59:42 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Search '=', key adress before '=', value adress after '='
 * @param str
 * @return t_env_n*
 */
static t_env_n	*ft_new_env_node(char *str)
{
	t_env_n	*node;
	char	*sep;

	sep = ft_strchr(str, '=');
	if (!sep)
		return (NULL);
	node = ft_calloc(1, sizeof(t_env_n));
	if (!node)
		return (NULL);
	node->key = ft_substr(str, 0, sep - str);
	node->value = ft_strdup(sep + 1);
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	return (node);
}

/**
 * @brief
 * Add node at the end of env, update last pointer.
 * @param env
 * @param node
 * @param last
 */
static void	ft_env_append(t_env *env, t_env_n *node, t_env_n **last)
{
	if (!env->head)
		env->head = node;
	else
		(*last)->next = node;
	*last = node;
}

/**
 * @brief
 * Init env linked list from envp array.
 * Each entry "KEY=value" becomes a node in the list.
 * @param envp
 * @return t_env*
 */
t_env	*ft_env_init(char **envp)
{
	t_env	*env;
	t_env_n	*node;
	t_env_n	*last;
	int		i;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	if (!envp)
	{
		free(env);
		return (NULL);
	}
	last = NULL;
	i = 0;
	while (envp[i])
	{
		node = ft_new_env_node(envp[i]);
		if (node)
			ft_env_append(env, node, &last);
		i++;
	}
	return (env);
}
