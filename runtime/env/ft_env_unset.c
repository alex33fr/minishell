/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:15:29 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/08 15:54:23 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Remove the node matching key from the env list and free it.
 * Return 0 whether the key was found or not.
 * @param env
 * @param key
 * @return int
 */
int	ft_env_unset(t_env *env, char *key)
{
	t_env_n	*prev;
	t_env_n	*current;

	if (!env || !key)
		return (1);
	current = env->head;
	prev = NULL;
	while (current)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				env->head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
