/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:09:44 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/03 15:49:38 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * Free node's
 * @param node 
 */
static void	ft_env_delone(t_env_n *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

/**
 * @brief 
 * Cleaning/free node's
 * @param env 
 */
void	ft_env_clear(t_env *env)
{
	t_env_n	*next;
	t_env_n	*current;

	if (!env)
		return ;
	current = env->head;
	while (current)
	{
		next = current->next;
		ft_env_delone(current);
		current = next;
	}
	free(env);
}
