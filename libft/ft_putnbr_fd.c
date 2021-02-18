/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:05:32 by mbelaman          #+#    #+#             */
/*   Updated: 2019/10/30 18:30:22 by mbelaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int tmp;

	if (n >= 0 && n < 10)
		ft_putchar_fd(n + '0', fd);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		tmp = n * -1;
		if (tmp < 10)
			ft_putchar_fd(tmp + '0', fd);
	}
	else
		tmp = n;
	if (tmp >= 10)
	{
		ft_putnbr_fd(tmp / 10, fd);
		ft_putnbr_fd(tmp % 10, fd);
	}
}
