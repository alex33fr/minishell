/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 13:41:11 by byonis            #+#    #+#             */
/*   Updated: 2026/05/13 14:19:27 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static char	*manage_herredoc_word(t_node *temp, char **envp, int last_status)
{
	char	*res;

	temp->heredoc_quoted = has_quotes(temp->value);
	if (!temp->heredoc_quoted)
		res = expand_and_remove_quotes(temp->value, envp, last_status);
	else
		res = unquoted(temp->value);
	return (res);
}

static int	transform_word_node(t_node *node, t_node *prev, char **envp, int ls)
{
	char	*res;

	if (prev && prev->token == T_HEREDOC)
		res = manage_herredoc_word(node, envp, ls);
	else
		res = expand_and_remove_quotes(node->value, envp, ls);
	if (!res)
		return (0);
	free(node->value);
	node->value = res;
	return (1);
}

t_queue	*do_expand(t_queue *q, char **envp, int last_status)
{
	t_node	*temp;
	t_node	*prev;

	temp = q->front;
	prev = NULL;
	while (temp && temp->token != T_EOF)
	{
		if (temp->token == T_WORD)
		{
			if (!transform_word_node(temp, prev, envp, last_status))
				return (NULL);
		}
		prev = temp;
		temp = temp->next;
	}
	return (q);
}
