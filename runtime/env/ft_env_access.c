/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:57:41 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/03 15:43:00 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * Return value associated to key in the env linked list.
 * Return NULL if key is not found.
 * @param env 
 * @param key 
 * @return char* 
 */
char	*ft_env_get(t_env *env, char *key)
{
	t_env_n	*node;

	if (!env || !key)
		return (NULL);
	node = env->head;
	while (node)
	{
		if (node->key && ft_strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}
