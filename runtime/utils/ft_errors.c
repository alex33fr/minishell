/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:48:14 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/27 11:31:23 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param s 
 * @return int 
 */
int	ft_export_err(char *s)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}
