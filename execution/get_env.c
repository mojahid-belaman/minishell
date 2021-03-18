/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:16:50 by knabouss          #+#    #+#             */
/*   Updated: 2021/03/17 16:30:26 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**split_env(char *line)
{
	char	**key_value;

	key_value = ft_split(line, '=');
	return (key_value);
}

t_env	*create_node(char **key_value)
{
	t_env	*list;

	list = (t_env *)malloc(sizeof(t_env));
	list->key = ft_strdup(key_value[0]);
	list->value = ft_strdup(key_value[1]);
	list->next = NULL;
	return (list);
}

t_env *get_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	char	**key_value;

	head = (t_env *)malloc(sizeof(t_env));
	head = NULL;
	while (*envp)
	{
		key_value = split_env(*envp);
		current = create_node(key_value);
		ft_lstadd_back(&head, current);
		envp++;
	}
	return (head);
}

t_envar	*get_envar(t_env *head)
{
	t_envar	*env;

	env = (t_envar *)malloc(sizeof(t_envar));
	while(head)
	{
		if (!(ft_strncmp("HOME", head->key, 4)))
			env->home = ft_strdup(head->value);
		else if (!(ft_strncmp("PWD", head->key, 3)))
			env->pwd = ft_strdup(head->value);
		else if (!(ft_strncmp("OLDPWD", head->key, 6)))
			env->oldpwd = ft_strdup(head->value);
		head = head->next;
	}
	return (env);
}
