/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:17:50 by mbelaman          #+#    #+#             */
/*   Updated: 2019/11/01 19:52:34 by mbelaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t lendst;
	size_t lensrc;
	size_t index;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	index = 0;
	if (size <= lendst)
		lensrc = lensrc + size;
	else
	{
		lensrc = lensrc + lendst;
		while (src[index] && lendst + 1 < size)
		{
			dst[lendst] = src[index];
			lendst++;
			index++;
		}
		dst[lendst] = '\0';
	}
	return (lensrc);
}
