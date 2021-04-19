#include "../headers/minishell.h"

char	*get_home(t_var *var)
{
	t_env	*current;

	current = var->head_env;
	while(current)
	{
		if (!(ft_strncmp("HOME", current->key, 4)))
			break;
		current = current->next;
	}
	if (current && current->print)
		return(ft_strdup(current->value));
	return (ft_strdup(var->home));
}

int		get_oldpwd(t_var *var)
{
	t_env *current;

	current = var->head_env;
	while (ft_strncmp("OLDPWD", current->key, 6) && current)
		current = current->next;
	if (!current || !current->print || current->print == 2)
	{
		printf("minishell : cd: OLDPWD not set\n");
		return (0);
	}
	*(var->prs->args + 1) = current->value;
	printf("%s\n", *(var->prs->args + 1));
	return (1);
}

void	chpwd_env(t_var *var)
{
	char	cwd[PATH_MAX];
	t_env	*pwd;
	t_env	*oldpwd;

	oldpwd = var->head_env;
	pwd = var->head_env;
	while(pwd && ft_strncmp("PWD", pwd->key, 4))
		pwd = pwd->next;
	while (oldpwd && ft_strncmp("OLDPWD", oldpwd->key, 6))
		oldpwd = oldpwd->next;
	if (!(getcwd(cwd, sizeof(cwd))))
	{
		pwd->value = ft_strjoin(pwd->value, "/");
		*(var->prs->args + 1) = ft_strjoin(pwd->value, *(var->prs->args + 1));
		printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
	}
	else
		*(var->prs->args + 1) = cwd;

	if (oldpwd->print == 1 && pwd->print == 1)
	{
		oldpwd->value = ft_strdup(pwd->value);
		pwd->value = ft_strdup(*(var->prs->args + 1));
	}
	else if (oldpwd->print == 2 && pwd->print == 1)
	{
		oldpwd->value = ft_strdup(pwd->value);
		pwd->value = ft_strdup(*(var->prs->args + 1));
		oldpwd->print = 3;
	}
	else if (oldpwd->print == 1 && pwd->print == 2)
	{
		oldpwd->value = ft_strdup("");
		pwd->value = ft_strdup(*(var->prs->args + 1));
		oldpwd->print = 2;
	}
	else if (oldpwd->print == 2 && pwd->print == 2)
	{
		oldpwd->value = ft_strdup(pwd->value);
		pwd->value = ft_strdup(*(var->prs->args + 1));
	}
}

char	*check_home(t_var *var)
{
	t_env *current;

	current = var->head_env;
	while(current && ft_strncmp("HOME", current->key, 4))
		current = current->next;
	if (!current || !current->print)
	{
		printf("minishell: cd: HOME not set\n");
		return(NULL);
	}
	else
		return(ft_strdup(current->value));
}

void	builtin_cd(t_var *var)
{
	int cd;
	if (!(*(var->prs->args + 1)))
	{
		*(var->prs->args + 1) = check_home(var);
		if (!(*(var->prs->args + 1)))
			return ;
	}
	else if (!(ft_strncmp("~", *(var->prs->args + 1), 1)))
		*(var->prs->args + 1) = ft_strjoin(get_home(var), *(var->prs->args + 1) + 1);
	else if (!(ft_strncmp("-", *(var->prs->args + 1), 1)))
		if(!(get_oldpwd(var)))
			return ;
	cd = chdir(*(var->prs->args + 1));
	if (cd < 0)
		printf("minishell: cd %s: No such file or directory\n", *(var->prs->args + 1));
	else
		chpwd_env(var);
}

void	builtin_pwd(t_var *var)
{
	char	pwd[PATH_MAX];
	t_env	*current;

	current = var->head_env;
	while(current && ft_strncmp("PWD", current->key, 3))
		current = current->next;
	if (current && current->print != 2)
		printf("%s\n", current->value);
	else
   		printf("%s\n", getcwd(pwd, sizeof(pwd)));
}

void    builtin_env(t_var *var)
{
	t_env	*current;

	current = var->head_env;
	while(current)
	{
		if (current->print == 1)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void    builtin_unset(t_var *var)
{
    t_env	*current;
    char    *tmp;
    int i = 1;

    while (*(var->prs->args + i))
    {
        current = var->head_env;
        while (current && ft_strncmp(*(var->prs->args + i), current->key, ft_strlen(current->key)))
            current = current->next;
        if (current)
        {
            tmp = current->value;
            current->value = ft_strdup("");
            current->print = 2;
            free(tmp);
        }
        i++;
    }
	var->status = 0;
}

void	builtin_exit(t_var *var)
{
	if (*(var->prs->args + 1))
	{
		if (ft_isdig(*(var->prs->args + 1)) && *(var->prs->args + 2))
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			var->exit = 1;
			return;
		}
		else if (!(ft_isdig(*(var->prs->args + 1))))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(*(var->prs->args + 1), 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit (-1);
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			exit(ft_atoi(*(var->prs->args + 1))); 
			// long long a = ft_atoi(*(var->prs->args + 1));
			// printf("%lld\n", a); 
		}
	}
	else
		exit(0);
}
