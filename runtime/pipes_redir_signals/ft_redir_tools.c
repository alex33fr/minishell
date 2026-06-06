/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 10:37:52 by aprivalo          #+#    #+#             */
/*   Updated: 2026/06/05 17:51:08 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Apply all redirections in the list in order. Return 1 on first failure.
 * @order 1.2.3.5.2.1
 */
static int	ft_apply_one_redir(t_redir *redir)
{
	int	status;

	if (redir->type == T_REDIRIN)
		status = ft_redir_in(redir->file);
	else if (redir->type == T_REDIROUT)
		status = ft_redir_out(redir->file);
	else if (redir->type == T_APPEND)
		status = ft_redir_join(redir->file);
	else if (redir->type == T_HEREDOC && redir->fd != -1)
	{
		status = dup2(redir->fd, STDIN_FILENO);
		if (status < 0)
			return (1);
		close(redir->fd);
		redir->fd = -1;
		return (0);
	}
	else
		status = 0;
	return (status);
}

int	ft_apply_redirs(t_redir *redir)
{
	int	status;

	while (redir)
	{
		status = ft_apply_one_redir(redir);
		if (status)
			return (1);
		redir = redir->next;
	}
	return (0);
}

/**
 * @brief
 * Open file read-only and redirect stdin from it. Return 1 on error.
 * @order 1.2.3.5.2.1.1
 */
int	ft_redir_in(char *file)
{
	int	fd_old;
	int	fd_new;

	fd_old = open(file, O_RDONLY);
	if (fd_old < 0)
	{
		perror(file);
		return (1);
	}
	fd_new = dup2(fd_old, STDIN_FILENO);
	if (fd_new < 0)
	{
		ft_close(fd_old, -1);
		perror("dup2");
		return (1);
	}
	ft_close(fd_old, -1);
	return (0);
}

/**
 * @brief
 * Open file for writing (create/truncate) and redirect stdout to it.
 * @order 1.2.3.5.2.1.2
 */
int	ft_redir_out(char *file)
{
	int	fd_old;
	int	fd_new;

	fd_old = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_old < 0)
		fd_old = open(file, O_WRONLY, 0);
	if (fd_old < 0)
	{
		perror(file);
		return (1);
	}
	fd_new = dup2(fd_old, STDOUT_FILENO);
	if (fd_new < 0)
	{
		ft_close(fd_old, -1);
		perror("dup2");
		return (1);
	}
	ft_close(fd_old, -1);
	return (0);
}

/**
 * @brief
 * Open file in append mode and redirect stdout to it. Return 1 on error.
 * @order 1.2.3.5.2.1.3
 */
int	ft_redir_join(char *file)
{
	int	fd_old;
	int	fd_new;

	fd_old = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_old < 0)
		fd_old = open(file, O_WRONLY, 0);
	if (fd_old < 0)
	{
		perror(file);
		return (1);
	}
	fd_new = dup2(fd_old, STDOUT_FILENO);
	if (fd_new < 0)
	{
		ft_close(fd_old, -1);
		perror("dup2");
		return (1);
	}
	ft_close(fd_old, -1);
	return (0);
}
