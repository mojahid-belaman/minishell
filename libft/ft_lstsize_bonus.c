/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:40:48 by mbelaman          #+#    #+#             */
/*   Updated: 2019/11/04 11:40:58 by mbelaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int cpt;

	cpt = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		cpt++;
		lst = lst->next;
	}
	return (cpt);
}
