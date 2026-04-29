/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:52:06 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/03 15:53:06 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * Find and return the node matching key in the env list.
 * Return NULL if not found.
 * @param env 
 * @param key 
 * @return t_env_n* 
 */
static t_env_n	*ft_env_find(t_env *env, char *key)
{
	t_env_n	*node;

	if (!env || !key)
		return (NULL);
	node = env->head;
	while (node)
	{
		if (node->key && ft_strcmp(node->key, key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * @brief
 * Allocate a new env node with key and value duplicated.
 * Fail return NULL.
 * @param key
 * @param value
 * @return t_env_n*
 */
static t_env_n	*ft_env_new_node_kv(char *key, char *value)
{
	t_env_n	*node;

	if (!key)
		return (NULL);
	node = ft_calloc(1, sizeof(t_env_n));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			free(node->key);
			free(node);
			return (NULL);
		}
	}
	node->next = NULL;
	return (node);
}

/**
 * @brief
 * Append new_node at the end of the env list.
 * Return 0 on success, 1 on failure.
 * @param env
 * @param new_node
 * @return int
 */
static int	ft_env_add_back(t_env *env, t_env_n *new_node)
{
	t_env_n	*last;

	if (!env || !new_node)
		return (1);
	if (!env->head)
	{
		env->head = new_node;
		return (0);
	}
	last = env->head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return (0);
}

/**
 * @brief
 * Set a variable in the env list.
 * Update its value if key already exists, add a new node otherwise.
 * Return 0 on success, 1 on failure.
 * @param env
 * @param key
 * @param value
 * @return int
 */
int	ft_env_set(t_env *env, char *key, char *value)
{
	t_env_n	*node;

	if (!env || !key)
		return (1);
	node = ft_env_find(env, key);
	if (node)
	{
		free(node->value);
		node->value = NULL;
		if (value)
			node->value = ft_strdup(value);
		if (value && !node->value)
			return (1);
		return (0);
	}
	node = ft_env_new_node_kv(key, value);
	if (!node)
		return (1);
	if (ft_env_add_back(env, node))
		return (1);
	return (0);
}
