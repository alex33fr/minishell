/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:13:42 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/06 08:26:30 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Write line + newline to fd, then free the line.
 * @order 1.2.3.5.2.1.4.1.0
 */
static void	ft_heredoc_write(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

/**
 * @brief
 * Disable ECHOCTL on stdin (storing original in *saved), configure signals
 * and readline for heredoc reading:
 *   - ECHOCTL cleared so terminal does not auto-echo "^C" on SIGINT.
 *     `c_lflag &= ~ECHOCTL` clears only the ECHOCTL bit:
 *       c_lflag  : 1 1 1 1
 *       ~ECHOCTL : 1 1 0 1
 *       result   : 1 1 0 1
 *   - rl_catch_signals = 0: prevents readline from installing its own SIGINT
 *     handler, so our SIGINT handler fires during readline.
 *   - SIGINT -> sig_int_heredoc (closes stdin to unblock readline),
 *     SIGQUIT ignored.
 * @order 1.2.3.5.2.1.4.1.3
 */
static void	ft_set_heredoc_sig(struct termios *saved)
{
	struct sigaction	sa;
	struct termios		raw;

	tcgetattr(STDIN_FILENO, saved);
	raw = *saved;
	raw.c_lflag = raw.c_lflag & ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	rl_catch_signals = 0;
	sa.sa_handler = sig_int_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief
 * Check stop conditions: signal, EOF, or delimiter match.
 * Free line and return 1 to break.
 * @order 1.2.3.5.2.1.4.1.4
 */
static int	ft_heredoc_check(char *line, char *delimiter)
{
	if (g_signal)
	{
		free(line);
		return (1);
	}
	if (!line)
	{
		ft_err_1();
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

/**
 * @brief
 * Expand line, write to fd, free resources. Return 1 to break on failure.
 * @order 1.2.3.5.2.1.4.1.5
 */
static int	ft_heredoc_process(int fd, char *line, t_env *env, int h_q)
{
	char	**envp;
	char	*expanded;

	if (h_q)
	{
		ft_heredoc_write(fd, line);
		return (0);
	}
	envp = ft_env_to_envp(env);
	expanded = expand_and_remove_quotes(line, envp, env->exit_code);
	free(line);
	ft_free_tab(envp);
	if (!expanded)
		return (1);
	ft_heredoc_write(fd, expanded);
	return (0);
}

/**
 * @brief
 * Read lines from stdin and write them to fd until delimiter or EOF is seen.
 * Backs up stdin (dup) before the loop and restores it (dup2) after, because
 * the SIGINT handler closes stdin to unblock readline. Restores termios and
 * normal shell signals whether the loop ended on delimiter, EOF, or SIGINT.
 * @order 1.2.3.5.2.1.4.1
 */
void	ft_heredoc_loop(int fd, char *delimiter, t_env *env, int h_q)
{
	char			*line;
	struct termios	saved;
	int				saved_stdin;
	int				status;

	saved_stdin = dup(STDIN_FILENO);
	ft_bzero(&saved, sizeof(saved));
	ft_set_heredoc_sig(&saved);
	while (1)
	{
		line = ft_read_heredoc_line();
		status = ft_heredoc_check(line, delimiter);
		if (status)
			break ;
		status = ft_heredoc_process(fd, line, env, h_q);
		if (status)
			break ;
	}
	dup2(saved_stdin, STDIN_FILENO);
	ft_close(saved_stdin, -1);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	rl_catch_signals = 1;
	ft_setup_signals();
}
