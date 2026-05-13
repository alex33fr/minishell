/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 12:37:52 by byonis            #+#    #+#             */
/*   Updated: 2026/05/13 12:50:41 by byonis           ###   ########.fr       */
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
	int				had_quotes;
	int				heredoc_quoted;
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
	int				saved_in;
	int				saved_out;
}	t_cmd;

typedef struct s_expand
{
	char	**envp;
	int		last_status;
	int		in_squote;
	int		in_dquote;
}	t_expand;

t_queue	*empty_queue(void);
int		enqueue(t_queue *queue, t_tok type, char *value, int had_quotes);
t_tok	dequeue(t_queue *queue, char **val_ptr);
void	clear_queue(t_queue *queue);

int		check_redir(t_queue *queue);
int		next_quote(char *line);
int		error_syntax(char *line, char *token);
int		manage_syntax_quotes(char *line, int *i, int *l_wp, int *l_wr);
int		manage_syntax_redir(char *line, int *i, int *l_wp, int *l_wr);
int		check_syntax(char *line);

int		search_token(t_queue *q, char *line);

int		next_token(char *line, t_tok tok);
t_tok	get_token_type(char *line);
char	*first_word(char *line, int *had_quotes);

int		ft_isspace(int c);
int		skip_spaces(char *line);
int		has_quotes(char *str);
char	*unquoted(char *str);
void	remove_quotes_delimiter(t_node *node);
t_queue	*do_expand(t_queue *q, char **envp, int last_status);
t_queue	*lexer(char *line, char **envp, int last_status);

void	free_cmds(t_cmd *cmds);

t_cmd	*init_cmd(t_queue *q);
int		manage_cmd_redir(t_queue *q, t_cmd *res);
void	manage_cmd_word(t_queue *q, t_cmd *res, int *i);

t_cmd	*create_cmds(t_queue *q);

char	*append(char *res, char *to_add);
char	*handle_dollar(char *str, int *i, t_expand *ex, char *res);
char	*expand_and_remove_quotes(char *str, char **envp, int last_status);

#endif