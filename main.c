/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:26:09 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/07 08:05:12 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/**
 * @brief 
 * Call + init 1 global var, for receiving signal 2 SIGINT from CTRL+C
 */
int	g_signal = 0;

/**
 * @brief [1.2.3] Tokenize, parse and execute one line. Free intermediates.
 * 1.2.3.1 add_history      — save to readline history
 * 1.2.3.2 ft_env_to_envp   — snapshot env as char**
 * 1.2.3.3 lexer            — tokenize into t_queue
 * 1.2.3.4 create_cmds      — parse into t_cmd list
 * 1.2.3.5 ft_exec_cmd_list — execute
 * @order 1.2.3
 */
static int	ft_run_line(char *line, t_shell *shell, int last_status)
{
	t_queue	*tokens;
	t_cmd	*cmds;
	char	**envp;

	if (!line || !*line)
		return (last_status);
	if (isatty(STDIN_FILENO))
		add_history(line);
	envp = ft_env_to_envp(shell->env);
	tokens = lexer(line, envp, last_status);
	ft_free_tab(envp);
	if (!tokens)
		return (2);
	cmds = create_cmds(tokens);
	clear_queue(tokens);
	if (!cmds)
		return (last_status);
	last_status = ft_exec_cmd_list(cmds, shell, last_status);
	free_cmds(cmds);
	return (last_status);
}

/**
 * @brief [1.2.2] Return 130 if SIGINT was received and reset the flag.
 * @order 1.2.2
 */
static int	ft_handle_signal(int last_status)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		return (130);
	}
	return (last_status);
}

/**
 * @brief [1.2] Read-eval loop. Exits on EOF or exit_flag.
 * 1.2.1 readline / ft_read_heredoc_line — read one line
 * 1.2.2 ft_handle_signal                — check SIGINT
 * 1.2.3 ft_run_line                     — tokenize, parse, exec
 * @order 1.2
 */
static int	ft_readline_loop(t_shell *shell)
{
	char	*line;
	int		last_status;
	int		interactive;

	last_status = 0;
	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		if (interactive)
			line = readline("minishell🔥66🔥$ ");
		else
			line = ft_read_heredoc_line();
		if (!line)
		{
			if (interactive)
				ft_putstr_fd("exit\n", 1);
			break ;
		}
		last_status = ft_handle_signal(last_status);
		last_status = ft_run_line(line, shell, last_status);
		free(line);
		if (shell->exit_flag)
			return (shell->exit_code);
	}
	return (last_status);
}

/**
 * @brief [1] Entry point.
 * 1.1 ft_init          — init shell (env + signals)
 * 1.2 ft_readline_loop — read-eval loop
 * 1.3 cleanup          — ft_env_clear, rl_clear_history, free
 * @order 1
 */
int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	int		status;

	(void)ac;
	(void)av;
	shell = ft_init(envp);
	if (!shell)
		return (1);
	status = ft_readline_loop(shell);
	ft_env_clear(shell->env);
	rl_clear_history();
	free(shell);
	return (status);
}
