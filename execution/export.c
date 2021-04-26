#include "../headers/minishell.h"

char	**envp_continue(t_env *current, char **key_value, int *i)
{
	char	*tmp;

	key_value[*i] = ft_strjoin(current->key, "=\"");
	tmp = key_value[*i];
	key_value[*i] = ft_strjoin(key_value[*i], current->value);
	free(tmp);
	tmp = NULL;
	tmp = key_value[*i];
	key_value[*i] = ft_strjoin(key_value[*i], "\"");
	free(tmp);
	tmp = NULL;
	(*i)++;
	return (key_value);
}

char	**envp(t_var *var)
{
	char	**key_value;
	t_env	*current;
	int		i;

	current = var->head_env;
	key_value = (char **)malloc((ft_listsize(var->head_env) + 1) \
	* sizeof(char *));
	i = 0;
	while (current)
	{
		if (current->print == 0)
		{
			key_value[i] = ft_strdup(current->key);
			i++;
		}
		else if (current->print == 1)
			key_value = envp_continue(current, key_value, &i);
		current = current->next;
	}
	key_value[i] = NULL;
	return (key_value);
}

char	**sort_key_value(t_var *var, char **key_value)
{
	char	*anothertmp;
	char	*tmp;
	int		j;
	int		i;

	i = -1;
	while (key_value[++i])
	{
		tmp = key_value[i];
		j = i + 1;
		while (j < ft_listsize(var->head_env))
		{
			if ((ft_strncmp(tmp, key_value[j], ft_strlen(tmp))) > 0)
			{
				anothertmp = tmp;
				tmp = key_value[j];
				key_value[j] = anothertmp;
			}
			key_value[i] = tmp;
			j++;
		}
	}
	return (key_value);
}

int	existing_value(t_var *var, char *key, char *value, int equal)
{
	t_env	*current;
	char	*tmp;

	current = var->head_env;
	var->plus = 0;
	if (key[ft_strlen(key) - 1] == '+')
	{
		var->plus = 1;
		tmp = key;
		key = ft_substr(key, 0, ft_strlen(key) - 1);
		free(tmp);
	}
	return (existing_value_bis(var, key, value, equal));
}

void	builtin_export(t_var *var)
{
	int		i;
	int		j;
	char	**key_value;

	j = -1;
	i = 0;
	if (!(var->prs->args[1]))
		export_env(var);
	else
	{
		while (var->prs->args[++i])
		{
			key_value = (char **)malloc(3 * sizeof(char *));
			key_value[2] = NULL;
			addvar_export(var, key_value, i);
			ft_free_args(key_value);
		}
	}
}
