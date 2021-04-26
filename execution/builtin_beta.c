#include "../headers/minishell.h"

char	*new_pwd(t_var *var, t_env *pwd, char *path)
{
	char	cwd[PATH_MAX];
	char	*tmp;

	if (!(getcwd(cwd, sizeof(cwd))))
	{
		tmp = pwd->value;
		pwd->value = ft_strjoin(pwd->value, "/");
		free(tmp);
		tmp = path;
		path = ft_strjoin(pwd->value, *(var->prs->args + 1));
		free(tmp);
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	else
	{
		tmp = path;
		path = ft_strdup(cwd);
		free(tmp);
	}
	return (path);
}

void	chpwd_bis(t_env *pwd, t_env *oldpwd, char *path)
{
	if (oldpwd->print == 1 && pwd->print == 1)
		replace_pwd(pwd, oldpwd, path);
	else if (oldpwd->print == 2 && pwd->print == 1)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup(pwd->value);
		free(pwd->value);
		pwd->value = ft_strdup(path);
		oldpwd->print = 3;
	}
	else if (oldpwd->print == 1 && pwd->print == 2)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup("");
		free(pwd->value);
		pwd->value = ft_strdup(path);
		oldpwd->print = 2;
	}
	else if (oldpwd->print == 2 && pwd->print == 2)
		replace_pwd(pwd, oldpwd, path);
	free(path);
}

void	chpwd_env(t_var *var)
{
	t_env	*pwd;
	char	*path;
	char	*tmp;
	t_env	*oldpwd;

	oldpwd = var->head_env;
	pwd = var->head_env;
	while (pwd && ft_strncmp("PWD", pwd->key, 4))
		pwd = pwd->next;
	while (oldpwd && ft_strncmp("OLDPWD", oldpwd->key, 6))
		oldpwd = oldpwd->next;
	if (*(var->prs->args + 1))
		path = ft_strdup(*(var->prs->args + 1));
	else
		path = NULL;
	tmp = path;
	path = new_pwd(var, pwd, path);
	chpwd_bis(pwd, oldpwd, path);
}

void	builtin_pwd(t_var *var)
{
	char	pwd[PATH_MAX];
	t_env	*current;

	current = var->head_env;
	while (current && ft_strncmp("PWD", current->key, 3))
		current = current->next;
	if (current && current->print != 2)
		printf("%s\n", current->value);
	else
		printf("%s\n", getcwd(pwd, sizeof(pwd)));
}

void	builtin_env(t_var *var)
{
	t_env	*current;

	current = var->head_env;
	while (current)
	{
		if (current->print == 1)
		{
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(current->value, 1);
			ft_putchar_fd('\n', 1);
		}
		current = current->next;
	}
}
