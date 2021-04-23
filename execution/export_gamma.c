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
	char	*tmp;
	int i;

	current = var->head_env;
	key_value = (char **)malloc((ft_listsize(var->head_env) + 1) * sizeof(char *));
	i = 0;
	while(current)
	{
		if (current->print == 0)
		{
			tmp = key_value[i];
			key_value[i] = ft_strdup(current->key);
			free(tmp);
			tmp = NULL;
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
	char *anothertmp;
	char *tmp;
	int j;
	int i;

	i = -1;
   while(key_value[++i])
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
	return(key_value);
}

void    export_env(t_var *var)
{
	char	**key_value;
	int i;
	int j;

	i = -1;
	key_value = envp(var);
	key_value = sort_key_value(var, key_value);
	while (key_value[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = -1;
		while (key_value[i][++j])
		{
			if (key_value[i][j] == '"' && key_value[i][j + 1] && key_value[i][j - 1] != '=')
				ft_putchar_fd('\\', 1);
			ft_putchar_fd(key_value[i][j], 1);
		}
		ft_putchar_fd('\n', 1);
	}
	ft_free_args(key_value);
}

int	check_args(t_var *var, char *current)
{
	int j;

	j = 0;
	if (!ft_isalpha(current[0]) && current[0] != '_')
	{
		ft_putstr_error("minishell: export: ", current, "not a valid identifier\n");
		var->status = 1;
		return (0);
	}
	while(current[++j])
	{
		if (ft_isalnum(current[j]) || (current[j] == '+' && !current[j + 1]) || current[j] == '_' )
			continue;
		else
		{
			ft_putstr_error("minishell: export: ", current, "not a valid identifier\n");
			var->status = 1;
			return (0);
		}
	}
	return (1);
}

int		existing_value(t_var *var, char *key, char *value, int equal)
{
	t_env *current;
	char *tmp;
	int		plus;

	current = var->head_env;
	plus = 0;
	if (key[ft_strlen(key) - 1] == '+')
	{
		plus = 1;
		tmp = key;
		key = ft_substr(key, 0, ft_strlen(key) - 1);
		free(tmp);
	}
	while (current)
	{
		if (!ft_strcmp(key, current->key))
		{
			tmp = current->value;
			if (!equal)
				return (1);
			if (plus)
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

void    builtin_export(t_var *var)
{
	int i;
	int j;
	int equal;
	char **key_value;
	t_env *current;

	j = -1;
	i = 0;
	key_value = (char **)malloc(3 * sizeof(char *));
	key_value[2] = NULL;
	if (!(var->prs->args[1]))
		export_env(var);
	else
	{
		while(var->prs->args[++i])
		{
			equal = 1;
			j = 0;
			while(var->prs->args[i][++j])
			{
				if (var->prs->args[i][j] == '=')
				{
					key_value[0] = ft_substr(var->prs->args[i], 0, j);
					key_value[1] = ft_substr(var->prs->args[i], j + 1, ft_strlen(var->prs->args[i]) - j);
					break;
				}
			}
			if (!var->prs->args[i][j])
			{
				key_value[0] = ft_substr(var->prs->args[i], 0, j);
				key_value[1] = ft_strdup("(null)");
				equal = 0;
			}
			if (!check_args(var, key_value[0]))
				break;
			if (!existing_value(var, key_value[0], key_value[1], equal))
			{
				current = create_node(key_value);
				ft_lstadd_back(&var->head_env, current);
			}
			ft_free_args(key_value);
		}
	}
}