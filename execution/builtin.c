#include "../headers/minishell.h"

char	*get_home(t_var *var)
{
	t_env	*current;

	current = var->head_env;
	while (current)
	{
		if (!(ft_strncmp("HOME", current->key, 4)))
			break ;
		current = current->next;
	}
	if (current && current->print == 1)
		return (ft_strdup(current->value));
	return (ft_strdup(var->home));
}

void	chpwd_env(t_var *var)
{
	char	cwd[PATH_MAX];
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
	chpwd_bis(pwd, oldpwd, path);
	// if (oldpwd->print == 1 && pwd->print == 1)
	// {
	// 	oldpwd->value = ft_strdup(pwd->value);
	// 	pwd->value = ft_strdup(path);
	// }
	// else if (oldpwd->print == 2 && pwd->print == 1)
	// {
	// 	oldpwd->value = ft_strdup(pwd->value);
	// 	pwd->value = ft_strdup(path);
	// 	oldpwd->print = 3;
	// }
	// else if (oldpwd->print == 1 && pwd->print == 2)
	// {
	// 	oldpwd->value = ft_strdup("");
	// 	pwd->value = ft_strdup(path);
	// 	oldpwd->print = 2;
	// }
	// else if (oldpwd->print == 2 && pwd->print == 2)
	// {
	// 	oldpwd->value = ft_strdup(pwd->value);
	// 	pwd->value = ft_strdup(path);
	// }
	// free(path);
}

char	*check_home(t_var *var)
{
	t_env	*current;

	current = var->head_env;
	while (current && ft_strncmp("HOME", current->key, 4))
		current = current->next;
	if (!current || !current->print)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	else
		return (ft_strdup(current->value));
}

void	builtin_cd(t_var *var)
{
	int		cd;
	char	*home;

	if (!(*(var->prs->args + 1)))
	{
		home = check_home(var);
		if (!home)
			return ;
		cd = chdir(home);
	}
	else if (!(ft_strncmp("~", *(var->prs->args + 1), 1)))
		*(var->prs->args + 1) = ft_strjoin(get_home(var), \
		*(var->prs->args + 1) + 1);
	if (*(var->prs->args + 1))
		cd = chdir(*(var->prs->args + 1));
	if (cd < 0)
		ft_putstr_error("minishell: cd: ", *(var->prs->args + 1), \
		": No such file or directory\n");
	else
		chpwd_env(var);
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

void	builtin_unset(t_var *var)
{
	t_env	*current;
	char	*tmp;
	int		i;

	i = 1;
	while (*(var->prs->args + i))
	{
		current = var->head_env;
		while (current && ft_strncmp(*(var->prs->args + i), \
		current->key, ft_strlen(current->key)))
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
			return ;
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
		}
	}
	else
		exit(var->status);
}
