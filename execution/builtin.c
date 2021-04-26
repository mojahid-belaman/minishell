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

char	*check_home(t_var *var)
{
	t_env	*current;

	current = var->head_env;
	while (current && ft_strncmp("HOME", current->key, 4))
		current = current->next;
	if (!current || !current->print)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		var->status = 1;
		return (NULL);
	}
	else
		return (ft_strdup(current->value));
}

void	builtin_cd(t_var *var)
{
	int		cd;
	char	*tmp;
	char	*home;

	if (!(*(var->prs->args + 1)))
	{
		home = check_home(var);
		if (!home)
			return ;
	}
	else if (!(ft_strncmp("~", *(var->prs->args + 1), 1)))
	{
		tmp = get_home(var);
		home = ft_strjoin(tmp, *(var->prs->args + 1) + 1);
		free(tmp);
	}
	else
		home = ft_strdup(*(var->prs->args + 1));
	cd = chdir(home);
	if (cd < 0)
		no_file(var, var->prs->cmd, home, ": No such file or directory\n");
	else
		chpwd_env(var);
	free(home);
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
