/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:40:00 by mbelaman          #+#    #+#             */
/*   Updated: 2019/11/04 11:40:09 by mbelaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *lst;

	lst = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}
