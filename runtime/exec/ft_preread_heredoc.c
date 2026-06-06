/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preread_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 11:04:17 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/05 17:48:41 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Heredoc reader child: close the read end, fill the pipe via ft_heredoc_loop,
 * then free every inherited resource (cmd list, saved fds, other heredoc fds,
 * env, history) and exit (130 if SIGINT was caught, else 0). Reading in a child
 * keeps the parent's readline state pristine and the child valgrind-clean.
 * @order 1.2.3.5.3.2.1.0
 */
static void	ft_heredoc_child(t_cmd *cmd, int *pfd, t_redir *redir, t_env *env)
{
	t_cmd	*head;
	int		code;

	ft_close(pfd[0], -1);
	ft_heredoc_loop(pfd[1], redir->file, env, redir->heredoc_quoted);
	ft_close(pfd[1], -1);
	code = 0;
	if (g_signal)
		code = 130;
	head = cmd;
	while (head->prev)
		head = head->prev;
	ft_close_heredoc_fds(head, NULL);
	ft_close(cmd->saved_in, cmd->saved_out);
	free_cmds(head);
	ft_env_clear(env);
	rl_clear_history();
	exit(code);
}

/**
 * @brief
 * Parent side: ignore SIGINT while the child reads, wait for it, restore the
 * normal signals. Set g_signal and return 1 if the child was interrupted
 * (killed by SIGINT or exited 130), 0 otherwise.
 * @order 1.2.3.5.3.2.1.0.1
 */
static int	ft_heredoc_wait(pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	ft_setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		g_signal = SIGINT;
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		g_signal = SIGINT;
	return (g_signal != 0);
}

/**
 * @brief
 * Open a pipe and fork a child to read one heredoc into it. On interrupt close
 * the pipe and return 1; otherwise store the read end in redir->fd. Forking
 * isolates readline so a heredoc Ctrl+C never corrupts the parent prompt.
 * @order 1.2.3.5.3.2.1.1
 */
static int	ft_read_one_heredoc(t_cmd *cmd, t_redir *redir, t_env *env)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (g_signal)
		return (1);
	status = pipe(pipefd);
	if (status == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		ft_heredoc_child(cmd, pipefd, redir, env);
	ft_close(pipefd[1], -1);
	status = ft_heredoc_wait(pid);
	if (status)
	{
		ft_close(pipefd[0], -1);
		return (1);
	}
	redir->fd = pipefd[0];
	return (0);
}

/**
 * @brief
 * Pre-read every heredoc of one command into its pipe. Return 1 on interrupt.
 * @order 1.2.3.5.3.2.1
 */
static int	ft_read_cmd_heredocs(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	int		status;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == T_HEREDOC)
		{
			status = ft_read_one_heredoc(cmd, redir, env);
			if (status)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

/**
 * @brief
 * Pre-read all heredocs in the command list and store their content in pipes.
 * Returns 1 immediately if g_signal is set (SIGINT).
 * @order 1.2.3.5.3.2
 */
int	ft_preread_heredocs(t_cmd *cmds, t_env *env)
{
	int	err;

	if (!cmds)
		return (0);
	while (cmds)
	{
		err = ft_read_cmd_heredocs(cmds, env);
		if (err)
			return (1);
		cmds = cmds->next;
	}
	return (0);
}
