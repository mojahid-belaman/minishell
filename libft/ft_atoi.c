/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:44:48 by mbelaman          #+#    #+#             */
/*   Updated: 2019/10/30 13:53:47 by mbelaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int convert;
	int sign;
	int index;

	convert = 0;
	index = 0;
	sign = 1;
	while (str[index] == '\t' || str[index] == '\n' || str[index] == '\f'
			|| str[index] == '\v' || str[index] == '\r' || str[index] == ' ')
		index++;
	if (str[index] == '+' && str[index + 1] == '-')
		return (0);
	if (str[index] == '+')
		index++;
	if (str[index] == '-')
	{
		sign = -1;
		index++;
	}
	while (str[index] != '\0' && str[index] >= '0' && str[index] <= '9')
	{
		convert = (convert * 10) + (str[index] - '0');
		index++;
	}
	return (convert * sign);
}
