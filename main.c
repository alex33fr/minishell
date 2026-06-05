/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:26:09 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/05 15:55:29 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_signal = 0;

/**
 * @brief
 * Lex and execute one input line. On no-interactive parse failure, set
 * exit_flag so the shell exits with code 2 (matches bash script behaviour).
 * @order 1.2.1
 */
static int	ft_run_line(char **pline, t_env *env, int last_status)
{
	t_queue	*tokens;
	char	**envp;
	char	*line;

	line = *pline;
	if (!line || !*line)
		return (last_status);
	if (isatty(STDIN_FILENO))
		add_history(line);
	envp = ft_env_to_envp(env);
	tokens = lexer(line, envp, last_status);
	ft_free_tab(envp);
	if (!tokens)
	{
		if (!isatty(STDIN_FILENO))
		{
			env->exit_flag = 1;
			env->exit_code = 2;
		}
		return (2);
	}
	last_status = ft_exec_cmds(tokens, pline, env, last_status);
	return (last_status);
}

/**
 * @brief
 * Read one line from stdin. If it ends with '|', concatenate the next line
 * so bash-style pipe continuation works in no-interactive mode.
 * @order 1.2.2
 */
static char	*ft_readline_nointeractive(void)
{
	char	*line;
	char	*next;
	char	*tmp;
	int		len;

	line = ft_read_heredoc_line();
	if (!line)
		return (NULL);
	len = (int)ft_strlen(line);
	if (!len || line[len - 1] != '|')
		return (line);
	next = ft_read_heredoc_line();
	if (!next)
		return (line);
	tmp = ft_strjoin(line, " ");
	free(line);
	line = ft_strjoin(tmp, next);
	free(tmp);
	free(next);
	return (line);
}

/**
 * @brief
 * Main read-eval loop.
 * Uses readline in interactive mode, ft_readline_nointeractive
 * otherwise. Exits when EOF or exit_flag is set.
 * @order 1.2.3
 */
static int	ft_readline_loop(t_env *env)
{
	char	*line;
	int		last_status;
	int		interactive;

	last_status = 0;
	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		if (interactive)
			line = readline("minishell66:$ ");
		else
			line = ft_readline_nointeractive();
		if (!line)
		{
			if (interactive)
				ft_putstr_fd("exit\n", 1);
			break ;
		}
		last_status = ft_handle_signal(last_status);
		last_status = ft_run_line(&line, env, last_status);
		free(line);
		if (env->exit_flag)
			return (env->exit_code);
	}
	return (last_status);
}

/**
 * @brief
 * Entry point. Init env, run readline loop,
 * clean up and return exit status.
 * @order 1
 */
int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		status;

	(void)ac;
	(void)av;
	env = ft_init(envp);
	if (!env)
		return (1);
	env->main_pid = getpid();
	status = ft_readline_loop(env);
	ft_env_clear(env);
	rl_clear_history();
	return (status);
}
