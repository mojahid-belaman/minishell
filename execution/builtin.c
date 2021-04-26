#include "../headers/minishell.h"

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
			var->status = 1;
			var->exit = 1;
			return ;
		}
		else if (!(ft_isdig(*(var->prs->args + 1))))
		{
			ft_putstr_error("exit\nminishell: exit: ", *(var->prs->args + 1), \
			": numeric argument required\n");
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

int	builtin(t_var *var)
{
	if (!(ft_strncmp("cd", *(var->prs->args), 3)) && !var->error)
		builtin_cd(var);
	else if (!(ft_strncmp("pwd", *(var->prs->args), 4)) && !var->error)
		builtin_pwd(var);
	else if (!(ft_strncmp("env", *(var->prs->args), 4)) && !var->error)
		builtin_env(var);
	else if (!(ft_strncmp("unset", *(var->prs->args), 6)) && !var->error)
		builtin_unset(var);
	else if (!(ft_strncmp("exit", *(var->prs->args), 5)) && !var->error)
		builtin_exit(var);
	else if (!(ft_strncmp("export", *(var->prs->args), 7)) && !var->error)
		builtin_export(var);
	else if (!(ft_strncmp("echo", *(var->prs->args), 5)) && !var->error)
		builtin_echo(var);
	else
		return (-1);
	return (0);
}
