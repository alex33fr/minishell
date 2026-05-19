/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_export_sort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:56:52 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/19 13:05:07 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Collect all env nodes into a malloc'd pointer array; set *size.
 * @order 1.2.3.5.2.2.2.4.2.1
 */
static t_env_n	**ft_collect_nodes(t_env *env, int *size)
{
	t_env_n		**nodes;
	t_env_n		*tmp;
	int			i;

	*size = 0;
	tmp = env->head;
	while (tmp && ++(*size))
		tmp = tmp->next;
	nodes = ft_calloc(*size + 1, sizeof(t_env_n *));
	if (!nodes)
		return (NULL);
	i = 0;
	tmp = env->head;
	while (tmp)
	{
		nodes[i++] = tmp;
		tmp = tmp->next;
	}
	return (nodes);
}

/**
 * @brief
 * Sort nodes array alphabetically by key using bubble sort.
 * @order 1.2.3.5.2.2.2.4.2.2
 */
static void	ft_bubble_sort_nodes(t_env_n **nodes, int size)
{
	t_env_n	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strcmp(nodes[j]->key, nodes[j + 1]->key) > 0)
			{
				tmp = nodes[j];
				nodes[j] = nodes[j + 1];
				nodes[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief
 * Print all env entries sorted alphabetically as "declare -x KEY=\"val\"".
 * @order 1.2.3.5.2.2.2.4.2
 */
int	ft_export_print_sorted(t_env *env)
{
	t_env_n	**nodes;
	int		size;
	int		i;

	nodes = ft_collect_nodes(env, &size);
	if (!nodes)
		return (1);
	ft_bubble_sort_nodes(nodes, size);
	i = 0;
	while (i < size)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(nodes[i]->key, 1);
		if (nodes[i]->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(nodes[i]->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
	free(nodes);
	return (0);
}
