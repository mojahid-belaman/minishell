/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:22:32 by mbelaman          #+#    #+#             */
/*   Updated: 2019/11/08 15:50:57 by mbelaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lennb(long nb)
{
	int		digit;

	digit = 0;
	if (nb == 0)
		digit++;
	if (nb < 0)
	{
		nb = nb * -1;
		digit++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		digit++;
	}
	return (digit);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		index;
	long	nb;

	nb = n;
	index = lennb(n);
	if (!(str = (char *)malloc(sizeof(char) * (index + 1))))
		return (NULL);
	str[index] = '\0';
	index--;
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		str[index] = nb % 10 + '0';
		nb = nb / 10;
		index--;
	}
	return (str);
}
