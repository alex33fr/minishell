/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:48:14 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/18 19:30:44 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Print "export: 's': not a valid identifier" to stderr, return 1.
 * @order 1.2.3.5.2.2.2.4.2
 */
int	ft_export_err(char *s)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

/**
 * @brief
 * Error 1: heredoc reached EOF before delimiter.
 */
void	ft_err_1(void)
{
	ft_putstr_fd("> \nwarning: here-document delimited by EOF\n", 2);
}

/**
 * @brief
 * Error 2: getcwd failed after chdir (cd internal).
 */
void	ft_err_2(void)
{
	ft_putstr_fd("cd: error retrieving current directory: getcwd:"
		" cannot access parent directories:"
		" No such file or directory\n", 2);
}

/**
 * @brief
 * Error 3: command or file not found after fork.
 */
void	ft_err_3(char *cmd, int is_path)
{
	ft_putstr_fd(cmd, 2);
	if (is_path)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
}

/**
 * @brief
 * Error 4: chdir failed, print "minishell: cd: " + perror.
 */
void	ft_err_4(char *target)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(target);
}
