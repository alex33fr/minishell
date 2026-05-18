/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_declare.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 00:00:00 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/18 00:00:00 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_n	**ft_collect_nodes(t_env *env, int size)
{
	t_env_n		**nodes;
	t_env_n		*tmp;
	int			i;

	nodes = ft_calloc(size + 1, sizeof(t_env_n *));
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

static void	ft_bubble_sort_nodes(t_env_n **nodes, int size)
{
	t_env_n		*tmp;
	int			i;
	int			j;

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

static void	ft_print_declare_nodes(t_env_n **nodes, int size)
{
	int	i;

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
}

/**
 * @brief
 * Implement declare -x: print env sorted alphabetically as "declare -x K="v"".
 * @order 1.2.3.5.2.2.2.8
 */
int	ft_builtin_declare(char **argv, t_env *env)
{
	t_env_n		**nodes;
	t_env_n		*node;
	int			size;

	if (argv[1] && ft_strcmp(argv[1], "-x"))
	{
		ft_putstr_fd("minishell: declare: only -x is supported\n", 2);
		return (2);
	}
	size = 0;
	node = env->head;
	while (node)
	{
		size++;
		node = node->next;
	}
	nodes = ft_collect_nodes(env, size);
	if (!nodes)
		return (1);
	ft_bubble_sort_nodes(nodes, size);
	ft_print_declare_nodes(nodes, size);
	free(nodes);
	return (0);
}
