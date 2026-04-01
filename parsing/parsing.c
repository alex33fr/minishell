/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:06:33 by byonis            #+#    #+#             */
/*   Updated: 2026/04/01 13:54:19 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void	clear(t_queue *q1, t_queue *q2, char *str1, char *str2)
{
	clear_queue(q1);
	clear_queue(q2);
	free(str1);
	free(str2);
}

t_queue *parsing(t_queue *lexer)
{
	t_queue	*res;
	char	*temp;
	char	*temp2;
	char	*space;

	if (!lexer)
		return (NULL);
	res = empty_queue();
	if (!res)
		return (NULL);
	while (lexer->front)
	{
		space = ft_strdup(" ");
		if (!space)
		{
			ft_putstr_fd("Error\n", 2);
			clear(lexer, res, temp, temp2);
			return (NULL);
		}
		if (lexer->front->value[0] == '<')
		{
			dequeue(lexer, &temp);
			if (lexer->front->token != T_WORD)
			{
				ft_putstr_fd("Error\n", 2);
				clear(lexer, res, temp, temp2);
				return (NULL);
			}
			dequeue(lexer, &temp2);
			temp = ft_strjoin_m(temp, space);
			if (!temp)
			{
				ft_putstr_fd("Error\n", 2);
				clear(lexer, res, temp, temp2);
				return (NULL);
			}
			temp = ft_strjoin_m(temp, temp2);
			if (!temp)
			{
				ft_putstr_fd("Error\n", 2);
				clear(lexer, res, temp, temp2);
				return (NULL);
			}
			enqueue(res, T_CMD, temp);
		}
		if (lexer->front->value[0] == '>')
		{
			dequeue(lexer, &temp);
			if (lexer->front->token != T_WORD)
			{
			ft_putstr_fd("Error\n", 2);
				clear(lexer, res, temp, temp2);
				return (NULL);
			}
			dequeue(lexer, &temp2);
			temp = ft_strjoin_m(temp, space);
			if (!temp)
			{
				ft_putstr_fd("Error\n", 2);
				clear(lexer, res, temp, temp2);
				return (NULL);
			}
			temp = ft_strjoin_m(temp, temp2);
			if (!temp)
			{
				ft_putstr_fd("Error\n", 2);
				clear(lexer, res, temp, temp2);
				return (NULL);
			}
			enqueue(res, T_CMD, temp);
		}
	}
	return (res);
}
