/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:34:43 by knabouss          #+#    #+#             */
/*   Updated: 2021/03/10 18:43:16 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_home(char **command, t_env *current)
{
	if (*(command + 1) == NULL || !(ft_strncmp("~", *(command + 1), 1)))
	{

		while(current->next != NULL &&  ft_strncmp("HOME", current->key, 4))
		{	
			// ft_putstr_fd("test\n", 1);
			current = current->next;
		}
		if (*(command + 1) == NULL || !(ft_strncmp("~", *(command + 1), 2)))
			*(command + 1) = current->value;
		else if (!(ft_strncmp("~/", *(command + 1), 2)))
			*(command + 1) = ft_strjoin(current->value, *(command + 1) + 1);
	}
	return (*(command + 1));
}

int		get_oldpwd(char **command, t_env *current)
{
	if (!(ft_strncmp("-", *(command + 1), 1)))
	{
		while (ft_strncmp("OLDPWD", current->key, 6) && current->next != NULL)
			current = current->next;
		if (current->next == NULL)
		{
			printf("minishell : cd: OLDPWD not set\n");
			return (0);
		}
		*(command + 1) = current->value;
		return (1);
	}
	return (1);
}

void	ch_pwd_env(char **command, t_env *current)
{
	char	*tmp;
	t_env	*head;
	struct	stat buffer;

	head = current;
	while(ft_strncmp("PWD", current->key, 3))
		current = current->next;
	tmp = current->value;
	while (ft_strncmp("OLDPWD", head->key, 6))
		head = head->next;
	if (lstat(*(command + 1), &buffer))
	{
		current->value = ft_strjoin(current->value, "/");
		current->value = ft_strjoin(current->value, *(command + 1));
	}
	else
		current->value = *(command + 1);
	head->value = tmp;
}

void	builtin_cd(char **command, t_env *current)
{
	int		cd;

	if (!(ft_strncmp("cd", *command, 2)))
	{
		*(command + 1) = get_home(command, current);
		if(!(get_oldpwd(command, current)))
			return ;
		cd = chdir(*(command + 1));
		if (cd >= 0)
			ch_pwd_env(command, current);
		else
			printf("cd %s: No such file or directory\n", *(command + 1));
	}
}

void	builtin_pwd(char **command, t_env *current)
{
	char	pwd[PATH_MAX];
	
	if(!(ft_strncmp("pwd", *command, 3)))
	{
		while(ft_strncmp("PWD", current->key, 3) && current->next != NULL)
			current = current->next;
		if (current->next != NULL)
		{
			printf("%s\n", current->value);
			return ;
		}
		else
    		printf("%s\n", getcwd(pwd, sizeof(pwd)));
	}
}

int     builtin_exit(char **command)
{
	if (!(ft_strncmp("exit", *command, 4)))
	{
		printf("%s\n",*command);	
		if (*(command + 1) != NULL && *(command + 2) != NULL)
			printf("minishell: exit: too many arguments\n");
		if (*(command + 1) != NULL)
			if (!(ft_isdigit(**(command + 1))))
			{
				printf("minishell: exit: %s: numeric argument required\n", *(command + 1));
				return (0);
			}
	}
	return (1);
}

int     verify_echo_n(char *str)
{
	if (*str != '-')
		return (0);
	str++;
	while(*str)
	{
		if (*str == 'n')
			str++;
		else
			return (0);
	}
	return (1);
}

void    builtin_echo(char **command)
{
	int		i;

	if (!(ft_strncmp("echo", *command, 4)))
	{
		if (!(verify_echo_n(*(command + 1))))
		{
			i = 1;
			while(*(command + i + 1))
			{
				printf("%s ", *(command + i));
				i++;
			}
			printf("%s\n", *(command + i));
		}
		else
		{
			i = 2;
			while(*(command + i + 1))
			{
				ft_putstr_fd(*(command + i), 1);
				ft_putchar_fd(' ', 1);
				i++;
			}
			ft_putstr_fd(*(command + i), 1);
		}
	}
}

void    builtin_env(char **command, t_env *head)
{
	if (!(ft_strncmp("env", *command, 3)))
	{
		while(head)
		{
			printf("%s=%s\n", head->key, head->value);
			head = head->next;
		}
	}
}
