#include "../headers/minishell.h"

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*lst;

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