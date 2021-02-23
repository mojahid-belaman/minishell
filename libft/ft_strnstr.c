/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 11:21:03 by mbelaman          #+#    #+#             */
/*   Updated: 2019/10/30 13:39:23 by mbelaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t pos;
	size_t i;

	pos = 0;
	i = 1;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[pos] != '\0')
	{
		if (str[pos] == to_find[0] && pos + i <= len)
		{
			while (to_find[i] != '\0' && str[pos + i] == to_find[i]
					&& pos + i <= len)
				i++;
			if (to_find[i] == '\0')
				return ((char *)&str[pos]);
		}
		pos++;
	}
	return (0);
}
