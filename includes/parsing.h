/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 12:37:52 by byonis            #+#    #+#             */
/*   Updated: 2026/04/01 13:37:43 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include "../libft/includes/libft.h"

// FAire une liste avec tab de tab ?
// Tant que token == T_WORD


typedef enum e_tok
{
	T_EOF,
	T_PIPE,
	T_REDIRIN,
	T_REDIROUT,
	T_HEREDOC,
	T_APPEND,
	T_WORD,
	T_CMD
}	t_tok;

typedef struct s_node
{
	t_tok			token;
	char			*value;
	struct s_node	*next;
}	t_node;

typedef struct s_queue
{
	t_node	*front;
	t_node	*back;
}	t_queue;

t_queue	*empty_queue(void);
int		enqueue(t_queue *queue, t_tok type, char *value);
t_tok	dequeue(t_queue *queue, char **val_ptr);
void	clear_queue(t_queue *queue);

int		search_token(t_queue *q, char *line);

int		next_token(char *line, t_tok tok);
char	*first_word(char *line);

int		ft_isspace(int c);
int		skip_spaces(char *line);
t_queue	*lexer(char *line);

#endif