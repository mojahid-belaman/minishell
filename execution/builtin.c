#include "../headers/minishell.h"

char	*get_home(char **command, t_env *current, t_envar *en_var)
{
	while(current)
	{
		if (!(ft_strncmp("HOME", current->key, 4)))
			break;
		current = current->next;
	}
	if (!current)
		return(ft_strdup(en_var->home));
	else
		return(ft_strdup(current->value));
}

int		get_oldpwd(char **command, t_env *current)
{
		while (ft_strncmp("OLDPWD", current->key, 6) && current)
			current = current->next;
		if (!current)
		{
			printf("minishell : cd: OLDPWD not set\n");
			return (0);
		}
		*(command + 1) = current->value;
		printf("%s\n", *(command + 1));
		return (1);
}

void	chpwd_env(char	**command, t_env *head, t_envar *en_var)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	t_env	*pwd;
	t_env	*oldpwd;

	oldpwd = head;
	pwd = head;
	while(pwd && ft_strncmp("PWD", pwd->key, 3))
		pwd = pwd->next;
	while (oldpwd && ft_strncmp("OLDPWD", oldpwd->key, 6))
		oldpwd = oldpwd->next;
	*(command + 1) = getcwd(cwd, sizeof(cwd));
	if (pwd && oldpwd)
	{
		tmp = pwd->value;
		pwd->value = ft_strdup(*(command + 1));
		oldpwd->value = ft_strdup(tmp);
	}
}
char	*check_home(char **command, t_env *current)
{
	while(current && ft_strncmp("HOME", current->key, 4))
		current = current->next;
	if (!current)
	{
		printf("minishell: cd: HOME not set\n");
		return(NULL);
	}
	else
		return(ft_strdup(current->value));
}

void	builtin_cd(char **command, t_env *current, t_envar *en_var)
{
	int cd;

	if (!(*(command + 1)))
	{
		*(command + 1) = check_home(command, current);
		if (!(*(command + 1)))
			return ;
	}
	else if (!(ft_strncmp("~", *(command + 1), 1)))
		*(command + 1) = ft_strjoin(get_home(command, current, en_var), *(command + 1) + 1);
	else if (!(ft_strncmp("-", *(command + 1), 1)))
		if(!(get_oldpwd(command, current)))
			return ;
	cd = chdir(*(command + 1));
	if (cd < 0)
		printf("minishell: cd %s: No such file or directory\n", *(command + 1));
	else
		chpwd_env(command, current, en_var);
}

void	builtin_pwd(char **command, t_env *current)
{
	char	pwd[PATH_MAX];

	while(current && ft_strncmp("PWD", current->key, 3))
		current = current->next;
	if (current)
		printf("%s\n", current->value);
	else
   		printf("%s\n", getcwd(pwd, sizeof(pwd)));
}

void    builtin_env(char **command, t_env *head)
{
	while(head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

void	builtin_unset(char	**command, t_env **head)
{
	t_env	*current;
	t_env	*previous;

	current = *head;
	if (!(*(command + 1)))
		return ;
	while (current && ft_strncmp(*(command + 1), current->key, ft_strlen(*(command + 1))))
	{
		previous = current;
		current = current->next;
	}
	if (current)
	{
		previous->next = current->next;
		free(current);
	}
}

void    builtin(char **command, t_env **current, t_envar *en_var)
{
	if (!(ft_strncmp("cd", *command, 2)))
		builtin_cd(command, *current, en_var);
	else if (!(ft_strncmp("pwd", *command, 3)))
		builtin_pwd(command, *current);
	else if (!(ft_strncmp("env", *command, 3)))
		builtin_env(command, *current);
	else if (!(ft_strncmp("unset", *command, 5)))
		builtin_unset(command, current); 
}