/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:16:50 by knabouss          #+#    #+#             */
/*   Updated: 2021/03/10 15:34:10 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**split_env(char *line)
{
	char	**key_value;

	key_value = ft_split(line, '=');
	return (key_value);
}

t_env	*create_node(t_env *node, char **key_value)
{
	t_env	*list;

	list = (t_env *)malloc(sizeof(t_env));
	list->key = ft_strdup(key_value[0]);
	list->value = ft_strdup(key_value[1]);
	list->next = NULL;
	return (list);
}

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

t_env *get_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	char	**key_value;

	head = NULL;
	while (*envp)
	{
		key_value = split_env(*envp);
		current = create_node(current, key_value);
		ft_lstadd_back(&head, current);
		envp++;
	}
	return (head);
}

t_envar	*get_envar(t_env *head)
{
	t_envar	*env;
	t_env	*tmp;

	tmp = head;
	while(tmp)
	{
		if (!(ft_strncmp("HOME", tmp->key, 4)))
			env->home = ft_strdup(tmp->value);
		else if (!(ft_strncmp("PWD", tmp->key, 3)))
			env->pwd = ft_strdup(tmp->value);
		else if (!(ft_strncmp("OLDPWD", tmp->key, 6)))
			env->oldpwd = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	return (env);
}
