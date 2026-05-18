/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:14:09 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/18 14:21:36 by aprivalo         ###   ########.fr       */
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
	int		exit_flag;
	int		exit_code;
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
	t_cmd	*cmd;
	char	**envp;
	pid_t	*pids;
}	t_exec;

int		ft_exec_cmd(t_cmd *cmd, t_env *env);
int		ft_is_builtin(char *cmd);
int		ft_exec_builtin(t_cmd *cmd, t_env *env);
int		ft_exec_external(t_cmd *cmd, t_env *env);
int		ft_wait_child(pid_t pid);
char	*ft_resolve_path(t_exec *exec);
void	ft_exec_child(t_exec *exec, char *path);
int		ft_is_path_cmd(char *cmd);
char	*ft_find_path(char *cmd, t_env *env);
char	*ft_join_cmd_path(char *dir, char *cmd);

int		ft_builtin_pwd(t_env *env);
int		ft_builtin_env(t_env *env);
int		ft_builtin_exit(t_cmd *cmd, t_env *env);
int		ft_builtin_echo(char **argv);
int		ft_builtin_cd(char **argv, t_env *env);
char	*ft_cd_target(char **argv, t_env *env);
int		ft_builtin_export(char **argv, t_env *env);
int		ft_builtin_unset(char **argv, t_env *env);
int		ft_builtin_declare(char **argv, t_env *env);
int		ft_is_valid_num(char *s);
long	ft_exit_atol(char *s, int *overflow);
int		ft_is_valid_name(char *s);
int		ft_is_n_flag(char *s);
char	*ft_read_heredoc_line(void);
void	sig_int_heredoc(int sig);
int		ft_preread_heredocs(t_cmd *cmds, t_env *env);
void	ft_heredoc_loop(int fd, char *delimiter, t_env *env);

/**
 * @brief
 * PIPES
 */
typedef struct s_pipe_fds
{
	int		prev_fd;
	int		pipefd[2];
	int		last;
	pid_t	*pids;
}	t_pipe_fds;

int		ft_exec_pipeline(t_cmd *cmds, int n_cmds, t_env *env);
int		ft_wait_all(pid_t *pids, int n_cmds);
void	ft_child(t_cmd *cmd, t_env *env, t_pipe_fds *fds);
void	ft_update_fds(t_pipe_fds *fds);
void	ft_close_heredoc_fds(t_cmd *head, t_cmd *skip);

/**
 * @brief
 * REDIRECTIONS
 */
int		ft_apply_redirs(t_redir *redir, t_env *env);
int		ft_redir_in(char *file);
int		ft_redir_out(char *file);
int		ft_redir_join(char *file);
int		ft_redir_heredoc(char *delimiter, t_env *env);

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
void	ft_setup_signals_exec(void);
void	ft_signals_child(void);

/**
 * @brief
 * TOOLS
 */
void	ft_free_tab(char **tab);
void	ft_close(int in_1, int in_2);
int		ft_exec_cmd_list(t_cmd *cmds, t_env *env, int last_status);
int		ft_export_err(char *s);
void	ft_err_1(void);
void	ft_err_2(void);
void	ft_err_3(char *cmd, int is_path);
void	ft_err_4(char *target);
int		ft_exit_err(t_env *env, char *arg);
int		ft_exit_parse_arg(t_env *env, char **args, char *arg, long *val);

#endif
