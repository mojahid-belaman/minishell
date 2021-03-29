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

char	*find_value(char *find)
{
	t_var *var = get_struc_var(NULL);
	t_env *current = var->head_env;
	while (current)
	{
		if (!ft_strncmp(current->key, find, ft_strlen(find)))
			break;
		current = current->next;
	}
	if (current && current->print)
		return (ft_strdup(current->value));
	return (ft_strdup(""));
}

int	ft_listsize(t_env *lst)
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
