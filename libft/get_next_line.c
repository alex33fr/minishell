/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:32:25 by byonis            #+#    #+#             */
/*   Updated: 2026/01/03 16:20:29 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	*read_file(int fd, char *str)
{
	ssize_t	x;
	char	*result;
	char	*temp;

	x = 1;
	result = str;
	while (x > 0)
	{
		temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!temp)
			return (NULL);
		x = read(fd, temp, BUFFER_SIZE);
		if (x < 0)
		{
			free(temp);
			free(result);
			return (NULL);
		}
		result = ft_strjoin_m(result, temp);
		if (!result)
			return (NULL);
		if (ft_strchr(result, '\n'))
			break ;
	}
	return (result);
}

static size_t	ft_line_size(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (ft_strchr(str, '\n'))
	{
		while (str[i] != '\n')
			i++;
		i++;
	}
	else if (ft_strchr(str, '\0'))
	{
		while (str[i] != '\0')
			i++;
	}
	return (i);
}

static char	*del_nchar(char *str, size_t n)
{
	size_t	size;
	size_t	i;
	char	*new;

	if (!str)
		return (NULL);
	size = ft_strlen(str);
	new = malloc((size - n + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size - n)
	{
		new[i] = str[n + i];
		i++;
	}
	free(str);
	new[size - n] = '\0';
	return (new);
}

static int	check_fd_free_str(int fd, char **str)
{
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
	{
		if (*str)
		{
			free(*str);
			*str = NULL;
		}
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*temp;

	if (!check_fd_free_str(fd, &str))
		return (NULL);
	str = read_file(fd, str);
	if (!str)
		return (NULL);
	temp = ft_substr_m(str, 0, ft_line_size(str));
	if (!temp)
		return (NULL);
	str = del_nchar(str, ft_line_size(str));
	if (!str)
	{
		free(temp);
		return (NULL);
	}
	if (str[0] == '\0' && temp[0] == '\0')
	{
		free(str);
		free(temp);
		str = NULL;
		return (str);
	}
	return (temp);
}
