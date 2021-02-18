/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:10:06 by mbelaman          #+#    #+#             */
/*   Updated: 2019/10/30 08:13:35 by mbelaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*tmp;
	int		len;
	int		index;

	index = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (index < len)
	{
		tmp[index] = f(index, s[index]);
		index++;
	}
	tmp[index] = '\0';
	return (tmp);
}
