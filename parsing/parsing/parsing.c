/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:06:33 by byonis            #+#    #+#             */
/*   Updated: 2026/05/06 13:55:52 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static t_cmd	*first_cmd(t_queue *q)
{
	t_cmd	*res;
	int		i;

	res = init_cmd(q);
	if (!res)
		return (NULL);
	i = 0;
	while (q->front->token != T_PIPE && q->front->token != T_EOF)
	{
		if (q->front->token == T_WORD)
			manage_cmd_word(q, res, &i);
		else if (q->front->token >= T_REDIRIN && q->front->token <= T_APPEND)
		{
			if (!manage_cmd_redir(q, res))
				return (NULL);
		}
		else
			dequeue(q, NULL);
	}
	return (res);
}

static void	add_cmd_back(t_cmd **head, t_cmd **current, t_cmd *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*current = *head;
	}
	else
	{
		(*current)->next = new_node;
		new_node->prev = *current;
		*current = new_node;
	}
}

t_cmd	*create_cmds(t_queue *q)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new_node;

	head = NULL;
	current = NULL;
	while (q->front->token != T_EOF)
	{
		if (q->front->token == T_PIPE)
		{
			dequeue(q, NULL);
			continue ;
		}
		new_node = first_cmd(q);
		if (!new_node)
		{
			free_cmds(head);
			return (NULL);
		}
		add_cmd_back(&head, &current, new_node);
	}
	return (head);
}
