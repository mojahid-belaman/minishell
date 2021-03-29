#include "../headers/minishell.h"

void	export_env()
{
	char    **key_value;
	char	*tmp;
	char	*anothertmp;
	t_var *var = get_struc_var(NULL);
	t_env   *current;
	int i = 0;
	int j = 0;
	key_value = (char **)malloc((ft_listsize(var->head_env) + 1) * sizeof(char *));
	current = var->head_env;
	while(current)
	{
		if (current->print == 1)
		{
			// key_value[i] = (char *)malloc(ft_strlen(current->key) + ft_strlen(current->value) + 1);
			key_value[i] = ft_strjoin(current->key, "=\"");
			tmp = key_value[i];
			key_value[i] = ft_strjoin(key_value[i], current->value);
			free(tmp);
			tmp = key_value[i];
			key_value[i] = ft_strjoin(key_value[i], "\"");
			free(tmp);
			i++;
		}
		else if (current->print == 0)
		{
			key_value[i] = ft_strdup(current->key);
			i++;
		}
		current = current->next;
	}
	i = 0;
	while(key_value[i])
	{
		tmp = key_value[i];
		j = i + 1;
		while(j < ft_listsize(var->head_env))
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
		i++;
	}
	i = 0;
	while(key_value[i])
	{
		// need to fix the " issue;
		printf("declare -x %s\n", key_value[i]);
		i++;
	}
}

void	export_var(int *j)
{
	int i = 0;
	char    **key_value;
	t_env	*current;
	char	*tmp;
	t_var *var = get_struc_var(NULL);

	key_value = (char **)malloc(3);
	if (!ft_isalpha(**(var->prs->args + (*j))))
	{
		printf("minishell: export: %s:not a valid identifier\n", *(var->prs->args + (*j)));
		return ;
	}
	while((*(var->prs->args + (*j)))[i] && (*(var->prs->args + (*j)))[i]!= '=' && ft_isalnum((*(var->prs->args + (*j)))[i]))
		i++;
	if ((*(var->prs->args + (*j)))[i] == '=' || !(*(var->prs->args + (*j)))[i])
	{
		if (!((*(var->prs->args + (*j)))[i]))
		{
			key_value[0] = ft_substr(*(var->prs->args + (*j)), 0, i);
			key_value[1] = ft_strdup("(null)");
		}
		else if ((*(var->prs->args + (*j)))[i + 1] == '\0')
		{
			key_value[0] = ft_substr(*(var->prs->args + (*j)), 0, i);
			key_value[1] = ft_strdup("");
		}
		else
		{
			key_value[0] = ft_substr(*(var->prs->args + (*j)), 0, i);
			key_value[1] = ft_substr(*(var->prs->args + (*j)), i + 1, ft_strlen(*(var->prs->args + (*j))) - i);
		}
		current = create_node(key_value);
		ft_lstadd_back(&var->head_env, current);
	}
	else if (!ft_isalpha((*(var->prs->args + (*j)))[i]))
	{
		if ((*(var->prs->args + (*j)))[i] == '+' && (*(var->prs->args + (*j)))[i + 1] == '=')
		{
			tmp = *(var->prs->args + (*j));
			*(var->prs->args + (*j)) = ft_strjoin(ft_substr(*(var->prs->args + (*j)), 0, i), ft_substr(*(var->prs->args + (*j)), i + 1, ft_strlen(*(var->prs->args + (*j))) - i - 1));
			export_var(j);
			free(tmp);
		}
		else
		{
			printf("minishell: export: %s:not a valid identifier\n", *(var->prs->args + (*j)));
			return ;
		}
	}
}

void    builtin_export()
{
	t_env	*current;
	char	*tmp;
	int		i;
	t_var *var = get_struc_var(NULL);

	i = 1;
	if (!(*(var->prs->args + 1)))
		export_env();
	else
	{
		while (*(var->prs->args + i))
		{
			current = var->head_env;
			while(current)
			{
				if (!(ft_strncmp(current->key, *(var->prs->args + i), ft_strlen(current->key))))
					if ((*(var->prs->args + i))[ft_strlen(current->key)] == '=' || !((*(var->prs->args + i))[ft_strlen(current->key)]) || ((*(var->prs->args + i))[ft_strlen(current->key)] == '+' && (*(var->prs->args + i))[ft_strlen(current->key) + 1] == '='))
						break;
				current = current->next;
			}
			if (!current)
			{
				export_var(&i);
			}
			else
			{
				if ((*(var->prs->args + i))[ft_strlen(current->key)] == '+' && (*(var->prs->args + i))[ft_strlen(current->key) + 1] == '=')
				{
					tmp = current->value;
					current->value = ft_strjoin(current->value, (*(var->prs->args + i)) + ft_strlen(current->key) + 2);
					free(tmp);
				}
				else if ((*(var->prs->args + i))[ft_strlen(current->key)])
				{
					tmp = current->value;
					current->value = ft_substr(*(var->prs->args + i), ft_strlen(current->key) + 1, ft_strlen(*(var->prs->args + i)) - ft_strlen(current->key));
					current->print = 1;
					free(tmp);
				}
			}
			i++;
		}
	}
}