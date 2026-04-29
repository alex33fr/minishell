/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:14:09 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/26 18:44:57 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

/**
 * @brief
 * ENV
 */
typedef struct s_env_n
{
	char			*key;
	char			*value;
	struct s_env_n	*next;
}	t_env_n;

typedef struct s_env
{
	t_env_n	*head;
}	t_env;

t_env	*ft_env_init(char **envp);
char	*ft_env_get(t_env *env, char *key);
int		ft_env_set(t_env *env, char *key, char *value);
int		ft_env_unset(t_env *env, char *key);
char	**ft_env_to_envp(t_env *env);
void	ft_env_clear(t_env *env);

/**
 * @brief
 * EXEC
 */
typedef struct s_exec
{
	char	**argv;
	t_env	*env;
}	t_exec;

int		ft_exec_cmd(char **argv, t_env *env);
int		ft_is_builtin(char *cmd);
int		ft_exec_builtin(char **argv, t_env *env);
int		ft_exec_external(char **argv, t_env *env);
int		ft_wait_child(pid_t pid);
char	*ft_resolve_path(t_exec *exec);
void	ft_exec_child(t_exec *exec, char *path, char **envp);
int		ft_is_path_cmd(char *cmd);
char	*ft_find_path(char *cmd, t_env *env);
char	*ft_join_cmd_path(char *dir, char *cmd);

int		ft_builtin_pwd(void);
int		ft_builtin_env(t_env *env);
int		ft_builtin_exit(char **argv);
int		ft_builtin_echo(char **argv);
int		ft_builtin_cd(char **argv, t_env *env);
int		ft_builtin_export(char **argv, t_env *env);
int		ft_builtin_unset(char **argv, t_env *env);
int		ft_is_valid_num(char *s);
long	ft_exit_atol(char *s, int *overflow);
int		ft_is_valid_name(char *s);
int		ft_is_n_flag(char *s);

/**
 * @brief
 * PIPES
 */
typedef struct s_pipe_fds
{
	int	prev_fd;
	int	pipefd[2];
	int	last;
}	t_pipe_fds;

int		ft_exec_pipeline(t_cmd *cmds, int n_cmds, t_env *env);
int		ft_wait_all(pid_t *pids, int n_cmds);
void	ft_child(t_cmd *cmd, t_env *env, t_pipe_fds *fds);
void	ft_update_fds(t_pipe_fds *fds);

/**
 * @brief
 * REDIRECTIONS
 */
int		ft_apply_redirs(t_redir *redir);
int		ft_redir_in(char *file);
int		ft_redir_out(char *file);
int		ft_redir_append(char *file);
int		ft_redir_heredoc(char *delimiter);

/**
 * @brief
 * INIT
 */
t_env	*ft_init(char **envp);

/**
 * @brief
 * SIGNALS
 */
void	ft_setup_signals(void);
void	ft_signals_child(void);

/**
 * @brief
 * TOOLS
 */
void	ft_free_tab(char **tab);
void	ft_close(int in_1, int in_2);
int		ft_exec_cmd_list(t_cmd *cmds, t_env *env, int last_status);
int		ft_export_err(char *s);

#endif
