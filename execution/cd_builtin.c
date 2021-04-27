#include "../headers/minishell.h"

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
