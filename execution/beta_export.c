#include "../headers/minishell.h"

int	add_var_bis(t_var *var, int i, int j, char	**key_value)
{
	if (var->prs->args[i][j] == '=')
	{
		key_value[0] = ft_substr(var->prs->args[i], 0, j);
		key_value[1] = ft_substr(var->prs->args[i], j + 1, \
		ft_strlen(var->prs->args[i]) - j);
		return (1);
	}
	return (0);
}

int	check_args(t_var *var, char *current)
{
	int	j;

	j = 0;
	if (!ft_isalpha(current[0]) && current[0] != '_')
	{
		no_file(var, "export: `", current, "` not a valid identifier\n");
		return (0);
	}
	while (current[++j])
	{
		if (ft_isalnum(current[j]) || (current[j] == '+' \
		&& !current[j + 1]) || current[j] == '_' )
			continue ;
		else
		{
			no_file(var, "export: `", current, "` not a valid identifier\n");
			return (0);
		}
	}
	return (1);
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

int	existing_value_bis(t_var *var, char *key, char *value, int equal)
{
	t_env	*current;
	char	*tmp;

	current = var->head_env;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
		{
			tmp = current->value;
			if (!equal)
				return (1);
			if (var->plus)
				current->value = ft_strjoin(current->value, value);
			else
			{
				current->value = ft_strdup(value);
				current->print = 1;
			}
			free(tmp);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	addvar_export(t_var *var, char	**key_value, int i)
{
	t_env	*current;
	int		j;
	int		equal;

	equal = 1;
	j = 0;
	while (var->prs->args[i][++j])
		if (add_var_bis(var, i, j, key_value))
			break ;
	if (!var->prs->args[i][j])
	{
		key_value[0] = ft_substr(var->prs->args[i], 0, j);
		key_value[1] = ft_strdup("(null)");
		equal = 0;
	}
	if (!check_args(var, key_value[0]))
		return (0);
	if (!existing_value(var, key_value[0], key_value[1], equal))
	{
		current = create_node(key_value);
		ft_lstadd_back(&var->head_env, current);
	}
	return (1);
}
