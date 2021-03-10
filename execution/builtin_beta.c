/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_beta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:19:40 by knabouss          #+#    #+#             */
/*   Updated: 2021/03/10 12:36:30 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// review the builtin_cd!!

char	*get_dir(char **command, t_env *current, t_envar *en_var)
{
	if (!(ft_strncmp(".", *(command + 1), 2)))
		*(command + 1) = en_var->pwd;
	else if (!(ft_strncmp("..", *(command + 1), 3)))
		*(command + 1) = en_var->oldpwd;
	return((*command + 1));
}

char	*get_home(char **command, t_env *current, t_envar *en_var)
{
	char	*home;

	while(current != NULL)
	{
		if (!(ft_strncmp("HOME", current->key, 4)))
			break;
		current = current->next;
	}
	if (current == NULL)
		home = ft_strdup(en_var->home);
	else
		home = ft_strdup(current->value);
	return (home);
}

void    builtin_cd(char **command, t_env *current, t_envar *en_var)
{
	int cd;

	if (!(ft_strncmp(".", *(command + 1), 2)) || !(ft_strncmp("..", *(command + 1), 3)))
		*(command + 1) = get_dir(command, current, en_var);
	else if (!(ft_strncmp("~", *(command + 1), 1)))
		*(command + 1) = ft_strjoin(get_home(command, current, en_var), *(command + 1) + 1);
	else if (!(ft_strncmp("-", *(command + 1), 1)))
}

void    builtin(char **command, t_env *current, t_envar *en_var)
{
	if (!(ft_strncmp("cd", *command, 2)))
		builtin_cd(command, current, en_var);
}