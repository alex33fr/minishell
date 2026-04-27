/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:26:09 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/27 12:09:43 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/**
 * @brief 
 * Call + init 1 global var, for receiving signal 2 SIGINT from CTRL+C
 */
int	g_signal = 0;

/**
 * @brief 
 * Reads one line from standard input. Limit buffer max 4096 chars per shot. 
 * The returned string does not include the newline character.
 * @return char* A newly allocated line, or NULL if nothing was read.
 */
static char	*ft_read_line(void)
{
	char	buf[4096];
	char	*line;
	char	c;
	int		i;
	int		ret;

	i = 0;
	while (i < 4095)
	{
		ret = read(STDIN_FILENO, &c, 1);
		if (ret <= 0)
			break ;
		if (c == '\n')
			break ;
		buf[i++] = c;
	}
	if (ret <= 0 && i == 0)
		return (NULL);
	buf[i] = '\0';
	line = ft_strdup(buf);
	return (line);
}
/**
 * @brief Parses and executes one input line.
 * 
 * Adds the line to the command history when running in interactive mode,
 * then tokenizes it, builds the command list, and executes it.
 * 
 * @param line The input line to parse and execute.
 * @param env The shell environment list.
 * @param last_status The exit status of the previous command.
 * @return int The updated exit status after execution,
 * or the previous status on failure.
 */

static int	ft_run_line(char *line, t_env *env, int last_status)
{
	t_queue	*tokens;
	t_cmd	*cmds;

	if (!line || !*line)
		return (last_status);
	if (isatty(STDIN_FILENO))
		add_history(line);
	tokens = lexer(line, ft_env_to_envp(env), last_status);
	if (!tokens)
		return (2);
	cmds = create_cmds(tokens);
	if (!cmds)
		return (last_status);
	last_status = ft_exec_cmd_list(cmds, env, last_status);
	return (last_status);
}

/**
 * @brief Updates the last exit status according to received signals.
 *
 * Checks if SIGINT was received, resets the global signal flag,
 * and returns the standard exit status for CTRL+C.
 *
 * @param last_status The current exit status.
 * @return int 130 if SIGINT was received, otherwise the current exit status.
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
 * @brief Runs the main shell input loop.
 *
 * Reads commands either with readline in interactive mode or with
 * ft_read_line in non-interactive mode. Each line is then handled,
 * executed, and freed before reading the next one.
 *
 * @param env The shell environment list.
 * @return int The last exit status before leaving the loop.
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
			line = readline("minishell🔥66🔥$ ");
		else
			line = ft_read_line();
		if (!line)
		{
			if (interactive)
				ft_putstr_fd("exit\n", 1);
			break ;
		}
		last_status = ft_handle_signal(last_status);
		last_status = ft_run_line(line, env, last_status);
		free(line);
	}
	return (last_status);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		status;

	(void)ac;
	(void)av;
	env = ft_init(envp);
	if (!env)
		return (1);
	status = ft_readline_loop(env);
	ft_env_clear(env);
	return (status);
}
