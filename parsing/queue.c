/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:38:21 by byonis            #+#    #+#             */
/*   Updated: 2026/03/31 12:52:36 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_queue	*empty_queue(void)
{
	t_queue	*result;

	result = malloc(sizeof(t_queue));
	if (!result)
		return (NULL);
	result->front = NULL;
	result->back = NULL;
	return (result);
}

static int	check_new_node(t_node *new_node, char *value)
{
	if (!value)
	{
		free(new_node);
		return (0);
	}
	return (1);
}

int	enqueue(t_queue *queue, t_tok type, char *value)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (0);
	new_node->token = type;
	new_node->value = value;
	new_node->next = NULL;
	if (queue->back == NULL)
	{
		queue->front = new_node;
		queue->back = new_node;
	}
	else
	{
		queue->back->next = new_node;
		queue->back = new_node;
	}
	return (1);
}

t_tok	dequeue(t_queue *queue, char **val_ptr)
{
	t_node	*temp;
	t_tok	type;

	if (!queue || !queue->front)
		return (T_EOF);
	temp = queue->front;
	type = temp->token;
	if (val_ptr)
		*val_ptr = temp->value;
	else
		free(temp->value);
	queue->front = queue->front->next;
	if (queue->front == NULL)
		queue->back = NULL;
	free(temp);
	return (type);
}

void	clear_queue(t_queue *queue)
{
	if (!queue)
		return ;
	while (queue->front)
		dequeue(queue, NULL);
	free(queue);
}
