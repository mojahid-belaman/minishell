#include "../headers/minishell.h"

void    chpwd_env(t_var *var)
{
	char	cwd[PATH_MAX];
	t_env	*pwd;
	char    *path;
	char    *tmp;
	t_env	*oldpwd;

	oldpwd = var->head_env;
	pwd = var->head_env;
	while(pwd && ft_strncmp("PWD", pwd->key, 4))
		pwd = pwd->next;
	while (oldpwd && ft_strncmp("OLDPWD", oldpwd->key, 6))
		oldpwd = oldpwd->next;
	getcwd(cwd, sizeof(cwd));
	path = ft_strdup(*(var->prs->args + 1));
	if (!cwd)
	{
		tmp = pwd->value;
		pwd->value = ft_strjoin(pwd->value, "/");
		free(tmp);
		tmp = path;
		path = ft_strjoin(pwd->value, *(var->prs->args + 1));
		free(tmp);
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 1);
	}
	else
	{
		tmp = path;
		path = ft_strdup(cwd);
		free(tmp);
	}
	if (oldpwd->print == 1 && pwd->print == 1)
	{
		oldpwd->value = ft_strdup(pwd->value);
		pwd->value = ft_strdup(path);
	}
	else if (oldpwd->print == 2 && pwd->print == 1)
	{
		oldpwd->value = ft_strdup(pwd->value);
		pwd->value = ft_strdup(path);
		oldpwd->print = 3;
	}
	else if (oldpwd->print == 1 && pwd->print == 2)
	{
		oldpwd->value = ft_strdup("");
		pwd->value = ft_strdup(path);
		oldpwd->print = 2;
	}
	else if (oldpwd->print == 2 && pwd->print == 2)
	{
		oldpwd->value = ft_strdup(pwd->value);
		pwd->value = ft_strdup(path);
	}
	free(path);
}

void	chpwd_env_old(t_var *var)
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
	{
		*(var->prs->args + 1) = cwd;
		*(var->prs->args + 2) = NULL;
	}
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
