#include "../headers/minishell.h"

char	*get_home()
{
	t_var *var = get_struc_var(NULL);
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

int		get_oldpwd()
{
	t_var *var = get_struc_var(NULL);
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

void	chpwd_env()
{
	t_var *var = get_struc_var(NULL);
	char	cwd[PATH_MAX];
	t_env	*pwd;
	t_env	*oldpwd;

	oldpwd = var->head_env;
	pwd = var->head_env;
	while(pwd && ft_strncmp("PWD", pwd->key, 4))
		pwd = pwd->next;
	while (oldpwd && ft_strncmp("OLDPWD", oldpwd->key, 6))
		oldpwd = oldpwd->next;
	*(var->prs->args + 1) = getcwd(cwd, sizeof(cwd));
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

char	*check_home()
{
	t_var *var = get_struc_var(NULL);
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

void	builtin_cd()
{
	int cd;
	t_var *var = get_struc_var(NULL);

	if (!(*(var->prs->args + 1)))
	{
		*(var->prs->args + 1) = check_home();
		if (!(*(var->prs->args + 1)))
			return ;
	}
	else if (!(ft_strncmp("~", *(var->prs->args + 1), 1)))
		*(var->prs->args + 1) = ft_strjoin(get_home(), *(var->prs->args + 1) + 1);
	else if (!(ft_strncmp("-", *(var->prs->args + 1), 1)))
		if(!(get_oldpwd()))
			return ;
	cd = chdir(*(var->prs->args + 1));
	if (cd < 0)
		printf("minishell: cd %s: No such file or directory\n", *(var->prs->args + 1));
	else
		chpwd_env();
}

void	builtin_pwd()
{
	char	pwd[PATH_MAX];
	t_var *var = get_struc_var(NULL);
	t_env	*current;

	current = var->head_env;
	while(current && ft_strncmp("PWD", current->key, 3))
		current = current->next;
	if (current && current->print != 2)
		printf("%s\n", current->value);
	else
   		printf("%s\n", getcwd(pwd, sizeof(pwd)));
}

void    builtin_env()
{
	t_var *var = get_struc_var(NULL);
	t_env	*current;

	current = var->head_env;
	while(current)
	{
		if (current->print == 1)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void    builtin_unset()
{
	t_var *var = get_struc_var(NULL);
    t_env	*current;
    char    *tmp;
    int i = 1;

    while (*(var->prs->args + i))
    {
        current = var->head_env;
        while (current && ft_strncmp(*(var->prs->args + i), current->key, ft_strlen(current->key)))
		{
            current = current->next;
        }
        if (current)
        {
            tmp = current->value;
            current->value = ft_strdup("");
            current->print = 2;
            free(tmp);
        }
        i++;
    }
}

int     builtin_exit()
{
	t_var *var = get_struc_var(NULL);

	if (*(var->prs->args + 1)&& *(var->prs->args + 2))
		printf("minishell: exit: too many arguments\n");
	if (*(var->prs->args + 1))
	{
		if (!(ft_isdigit(**(var->prs->args + 1))))
		{
			printf("minishell: exit: %s: numeric argument required\n", *(var->prs->args + 1));
			exit (-1);
		}
		else
			exit(ft_atoi(*(var->prs->args + 1))) ; 
	}
	exit (0);
}
