/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:47:57 by byonis            #+#    #+#             */
/*   Updated: 2025/12/30 15:48:30 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	number_of_words(char const *s, char c)
{
	int		i;
	size_t	cpt;

	i = 0;
	cpt = 0;
	if (s == 0)
		return (0);
	while (s[i])
	{
		if (i > 0 && s[i] != c && s[i - 1] == c)
			cpt++;
		if (i == 0 && s[i] != c)
			cpt++;
		i++;
	}
	return (cpt);
}

int	word_size(char const *s, char c, int i)
{
	int	cpt;

	cpt = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i] != c && s[i])
	{
		cpt++;
		i++;
	}
	return (cpt);
}

int	check_tab(char **tab, int i)
{
	int	k;

	k = i;
	if (tab[k] == 0)
	{
		while (k >= 0)
		{
			free(tab[k]);
			k--;
		}
		free(tab);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	unsigned int		i;
	int					j;
	size_t				size;
	char				**tab;

	i = 0;
	j = 0;
	size = number_of_words(s, c);
	tab = malloc((size + 1) * sizeof(char *));
	if (tab == 0)
		return (0);
	tab[size] = 0;
	while (s != 0 && s[i])
	{
		if (s[i] != c)
		{
			tab[j] = ft_substr(s, i, word_size(s, c, i));
			if (!check_tab(tab, j))
				return (0);
			j++;
			i += word_size(s, c, i) - 1;
		}
		i++;
	}
	return (tab);
}
