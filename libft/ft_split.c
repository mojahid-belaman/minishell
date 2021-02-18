/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 09:19:56 by mbelaman          #+#    #+#             */
/*   Updated: 2019/11/11 13:15:10 by mbelaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**free_tab(char ***t, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free((*t)[i]);
		i++;
	}
	free(*t);
	return (NULL);
}

static int		word_count(char const *str, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if ((str[i] != c && str[i + 1] == c) ||
				(str[i] != c && str[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int		wd_l(char const *str, char c)
{
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			counter++;
			i++;
		}
		break ;
	}
	return (counter);
}

static char		**ft_split_continue(char *tmp, char c, char **tab)
{
	int		co;
	int		i;
	int		li;

	i = 0;
	li = 0;
	while (tmp[i])
	{
		while (tmp[i] == c && tmp[i])
			i++;
		if (!(tab[li] = (char *)malloc(sizeof(char) * (wd_l(tmp + i, c) + 1))))
			return (free_tab(&tab, li));
		co = 0;
		while (tmp[i] != c && tmp[i])
			tab[li][co++] = tmp[i++];
		tab[li++][co] = '\0';
	}
	tab[li] = NULL;
	return (tab);
}

char			**ft_split(char const *str, char c)
{
	char	**tab;
	char	*tmp;

	if (str == NULL)
		return (NULL);
	if (!(tmp = ft_strtrim(str, &c)))
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (word_count(tmp, c) + 1))))
		return (NULL);
	tab = ft_split_continue(tmp, c, tab);
	free(tmp);
	return (tab);
}
