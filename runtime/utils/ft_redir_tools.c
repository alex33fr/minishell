/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 10:37:52 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/27 11:31:46 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param redir 
 * @return int 
 */
int	ft_apply_redirs(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == T_REDIRIN && ft_redir_in(redir->file))
			return (1);
		if (redir->type == T_REDIROUT && ft_redir_out(redir->file))
			return (1);
		if (redir->type == T_APPEND && ft_redir_append(redir->file))
			return (1);
		if (redir->type == T_HEREDOC && ft_redir_heredoc(redir->file))
			return (1);
		redir = redir->next;
	}
	return (0);
}

/**
 * @brief 
 * 
 * @param file 
 * @return int 
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
 * 
 * @param file 
 * @return int 
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
 * 
 * @param file 
 * @return int 
 */
int	ft_redir_append(char *file)
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
