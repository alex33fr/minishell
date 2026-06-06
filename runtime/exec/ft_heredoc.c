/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:13:42 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/06 18:09:56 by aprivalo         ###   ########.fr       */
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
	int				status;
	int				saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	ft_setup_signals_heredoc();
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
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	ft_setup_signals();
}
