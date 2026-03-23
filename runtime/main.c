/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:26:09 by aprivalo          #+#    #+#             */
/*   Updated: 2026/04/03 15:11:51 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)av;
	(void)ac;
	env = ft_env_init(envp);
	if (!env)
		return (1);
	printf("PATH = %s\n", ft_env_get(env, "PATH"));
	printf("HOME = %s\n", ft_env_get(env, "HOME"));
	printf("USER = %s\n", ft_env_get(env, "USER"));
	ft_env_clear(env);
	return (0);
}
