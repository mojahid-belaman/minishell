#include "../headers/minishell.h"

char	*get_home(t_env *current)
{
	while(current)
	{
		if (!(ft_strncmp("HOME", current->key, 4)))
			break;
		current = current->next;
	}
	if (current)
		return(ft_strdup(current->value));
	return (NULL);
}

int		get_oldpwd(char **command, t_env *current)
{
		while (ft_strncmp("OLDPWD", current->key, 6) && current)
			current = current->next;
		if (!current || !current->print)
		{
			printf("minishell : cd: OLDPWD not set\n");
			return (0);
		}
		*(command + 1) = current->value;
		printf("%s\n", *(command + 1));
		return (1);
}

void	chpwd_env(char	**command, t_env *head)
{
	char	cwd[PATH_MAX];
	t_env	*pwd;
	t_env	*oldpwd;

	oldpwd = head;
	pwd = head;
	while(pwd && ft_strncmp("PWD", pwd->key, 3))
		pwd = pwd->next;
	while (oldpwd && ft_strncmp("OLDPWD", oldpwd->key, 6))
		oldpwd = oldpwd->next;
	*(command + 1) = getcwd(cwd, sizeof(cwd));
	if (oldpwd->print && pwd->print)
	{
		oldpwd->value = ft_strdup(pwd->value);
		pwd->value = ft_strdup(*(command + 1));
	}
	else if (pwd->print && !oldpwd->print)
	{
		pwd->value = ft_strdup(*(command + 1));
		oldpwd->value = ft_strdup(pwd->value);
		oldpwd->print = 0;
	}
	else if (!oldpwd->print || !pwd->print)
	{
		oldpwd->value = ft_strdup("");
		pwd->value = ft_strdup(*(command + 1));
		oldpwd->print = 0;
	}
}

char	*check_home(t_env *current)
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

void	builtin_cd(char **command, t_env *current)
{
	int cd;

	if (!(*(command + 1)))
	{
		*(command + 1) = check_home(current);
		if (!(*(command + 1)))
			return ;
	}
	else if (!(ft_strncmp("~", *(command + 1), 1)))
		*(command + 1) = ft_strjoin(get_home(current), *(command + 1) + 1);
	else if (!(ft_strncmp("-", *(command + 1), 1)))
		if(!(get_oldpwd(command, current)))
			return ;
	cd = chdir(*(command + 1));
	if (cd < 0)
		printf("minishell: cd %s: No such file or directory\n", *(command + 1));
	else
		chpwd_env(command, current);
}

void	builtin_pwd(t_env *current)
{
	char	pwd[PATH_MAX];

	while(current && ft_strncmp("PWD", current->key, 3))
		current = current->next;
	if (current)
		printf("%s\n", current->value);
	else
   		printf("%s\n", getcwd(pwd, sizeof(pwd)));
}

void    builtin_env(t_env *head)
{
	while(head)
	{
		if (head->print)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

void    builtin_unset(char	**command, t_env **head)
{
    t_env	*current;
    char    *tmp;
    int i = 1;

    while (*(command + i))
    {
        current = *head;
        while (current && ft_strncmp(*(command + i), current->key, ft_strlen(current->key)))
		{
            current = current->next;
        }
        if (current)
        {
            tmp = current->value;
            current->value = ft_strdup("");
            current->print = 0;
            free(tmp);
        }
        i++;
    }
}

int     builtin_exit(char **command)
{
	printf("%s\n",*command);	
	if (*(command + 1)&& *(command + 2))
		printf("minishell: exit: too many arguments\n");
	if (*(command + 1))
	{
		if (!(ft_isdigit(**(command + 1))))
		{
			printf("minishell: exit: %s: numeric argument required\n", *(command + 1));
			exit (-1);
		}
		else
			exit(ft_atoi(*(command + 1))) ; 
	}
	exit (0);
}

void    builtin(char **command, t_env **current)
{
	if (!(ft_strncmp("cd", *command, 3)))
		builtin_cd(command, *current);
	else if (!(ft_strncmp("pwd", *command, 4)))
		builtin_pwd(*current);
	else if (!(ft_strncmp("env", *command, 4)))
		builtin_env(*current);
	else if (!(ft_strncmp("unset", *command, 6)))
		builtin_unset(command, current);
	else if (!(ft_strncmp("exit", *command, 5)))
		builtin_exit(command);
	else if (!(ft_strncmp("export", *command, 7)))
		builtin_export(command, current);
	else
		printf("minishell: %s: command not found\n", *command);
}