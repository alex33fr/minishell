/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:14:09 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/09 17:48:47 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
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

/**
 * @brief 
 * TOOLS
 */
void	ft_free_tab(char **tab);
void	ft_close(int in_1, int in_2);
int		ft_strcmp(char *s1, char *s2);
#endif
