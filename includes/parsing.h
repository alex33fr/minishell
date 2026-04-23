/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 12:37:52 by byonis            #+#    #+#             */
/*   Updated: 2026/04/23 10:42:50 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include "../libft/includes/libft.h"

typedef enum e_tok
{
	T_EOF,
	T_PIPE,
	T_REDIRIN,
	T_REDIROUT,
	T_HEREDOC,
	T_APPEND,
	T_WORD,
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

typedef struct s_redir
{
	t_tok			type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

t_queue	*empty_queue(void);
int		enqueue(t_queue *queue, t_tok type, char *value);
t_tok	dequeue(t_queue *queue, char **val_ptr);
void	clear_queue(t_queue *queue);

int		check_redir(t_queue *queue);
int		check_pipe_quotes(char *line);

int		search_token(t_queue *q, char *line);

int		next_token(char *line, t_tok tok);
t_tok	get_token_type(char *line);
char	*first_word(char *line);

int		ft_isspace(int c);
int		skip_spaces(char *line);
t_queue	*do_expand(t_queue *q, char **envp);
t_queue	*lexer(char *line, char **envp);

void	free_cmds(t_cmd *cmds);

t_cmd	*first_cmd(t_queue *q);

t_cmd	*create_cmds(t_queue *q);

char	*var_replaced(char *var, char **envp, int pos);
char	*var_extraction(char *str, int pos);
// char	*replace(char *var, char *var_replaced, int pos);
char 	*expand(char *str, char **envp);
int		find_the_next_valid_variable(char *str, int start);

#endif