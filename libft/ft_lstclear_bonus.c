/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:42:58 by mbelaman          #+#    #+#             */
/*   Updated: 2019/11/04 11:43:05 by mbelaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *l;

	l = *lst;
	if (*lst == NULL)
		return ;
	while (l)
	{
		del((*lst)->content);
		l = (*lst)->next;
		free(*lst);
		*lst = l;
	}
	*lst = NULL;
}
