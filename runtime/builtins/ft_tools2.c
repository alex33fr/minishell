/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprivalo <aprivalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:02:48 by aprivalo          #+#    #+#             */
/*   Updated: 2026/05/23 00:38:47 by aprivalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pid_str(void)
{
	pid_t	pid;
	char	*res;

	pid = getpid();
	res = ft_itoa(pid);
	return (res);
}

/**
 * @brief
 * Write each word separated by spaces. Return 1 on write error.
 * @order 1.2.3.5.2.2.2.1.2
 */
static int	ft_echo_words(char **argv, int i)
{
	int	state;
	int	size;

	while (argv[i])
	{
		size = ft_strlen(argv[i]);
		state = write(1, argv[i], size);
		if (state == -1)
			return (1);
		if (argv[i + 1])
		{
			state = write(1, " ", 1);
			if (state == -1)
				return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief
 * Print argv words separated by spaces, with newline unless -n flag is set.
 * @order 1.2.3.5.2.2.2.1
 */
int	ft_builtin_echo(char **argv)
{
	int	newline;
	int	i;
	int	state;

	newline = 1;
	i = 1;
	while (argv[i] && ft_is_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	state = ft_echo_words(argv, i);
	if (state)
		return (1);
	if (newline)
	{
		state = write(1, "\n", 1);
		if (state == -1)
		{
			perror("echo: write error");
			return (1);
		}
	}
	return (0);
}

/**
 * @brief
 * Check too-many-args and parse numeric val from arg. Return 0 on success.
 * @order 1.2.3.5.2.2.2.7.3
 */
int	ft_exit_parse_arg(t_env *env, char **args, char *arg, long *val)
{
	int	err;

	if (args[2])
	{
		free(arg);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	err = 0;
	*val = ft_exit_atol(arg, &err);
	if (err)
	{
		ft_exit_err(env, arg);
		return (2);
	}
	return (0);
}

int	ft_export_no_value(char *key, t_env *env)
{
	t_env_n	*node;
	int		status;

	node = env->head;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (0);
		node = node->next;
	}
	status = ft_env_set(env, key, NULL);
	return (status);
}
