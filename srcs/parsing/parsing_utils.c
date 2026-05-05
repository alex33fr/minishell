/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 13:32:55 by byonis            #+#    #+#             */
/*   Updated: 2026/04/30 15:00:43 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	args_number_in_cmd(t_queue *q)
{
	t_node	*temp;
	int		count_redir;
	int		count_word;

	if (!q || !q->front)
		return (0);
	temp = q->front;
	count_word = 0;
	count_redir = 0;
	while (temp && temp->token != T_PIPE && temp->token != T_EOF)
	{
		if (temp->token == T_WORD)
			count_word++;
		if (temp->token == T_REDIRIN || temp->token == T_REDIROUT
			|| temp->token == T_APPEND || temp->token == T_HEREDOC)
			count_redir++;
		temp = temp->next;
	}
	count_word -= count_redir;
	return (count_word);
}

static int	add_redir_back(t_redir **redirs, t_tok tok, char *file)
{
	t_redir	*new_node;
	t_redir	*temp;

	new_node = ft_calloc(1, sizeof(t_redir));
	if (!new_node)
		return (0);
	new_node->file = file;
	new_node->type = tok;
	new_node->next = NULL;
	if (!*redirs)
		*redirs = new_node;
	else
	{
		temp = *redirs;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	return (1);
}

static t_cmd	*init_cmd(t_queue *q)
{
	t_cmd	*res;
	int		nb_args;

	res = ft_calloc(1, sizeof(t_cmd));
	if (!res)
		return (NULL);
	nb_args = args_number_in_cmd(q);
	res->args = ft_calloc(nb_args + 1, sizeof(char *));
	if (!res->args)
	{
		free(res);
		return (NULL);
	}
	res->redir = NULL;
	return (res);
}

static int	manage_cmd_redir(t_queue *q, t_cmd *res)
{
	t_tok	redir_type;
	char	*file;

	redir_type = q->front->token;
	dequeue(q, NULL);
	if (q->front->token == T_WORD)
	{
		dequeue(q, &file);
		if (!add_redir_back(&res->redir, redir_type, file))
		{
			free_cmds(res);
			return (0);
		}
	}
	return (1);
}

t_cmd	*first_cmd(t_queue *q)
{
	t_cmd	*res;
	char	*tmp;
	int		i;

	res = init_cmd(q);
	if (!res)
		return (NULL);
	i = 0;
	while (q->front->token != T_PIPE && q->front->token != T_EOF)
	{
		if (q->front->token == T_WORD)
		{
			dequeue(q, &tmp);
			res->args[i++] = remove_quotes(tmp);
		}
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
