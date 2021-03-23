#include "../headers/minishell.h"

void	export_env(t_env **head)
{
	char    **key_value;
	char	*tmp;
	char	*anothertmp;
	t_env   *current;
	int i = 0;
	int j = 0;
	key_value = (char **)malloc((ft_listsize(*head) + 1) * sizeof(char *));
	current = *head;
	while(current)
	{
		if (current->print)
		{
			key_value[i] = (char *)malloc(ft_strlen(current->key) + ft_strlen(current->value) + 1);
			key_value[i] = ft_strjoin(current->key, "=\"");
			tmp = key_value[i];
			key_value[i] = ft_strjoin(key_value[i], current->value);
			free(tmp);
			tmp = key_value[i];
			key_value[i] = ft_strjoin(key_value[i], "\"");
			free(tmp);
		}
		else
			key_value[i] = ft_strdup(current->key);
		i++;
		current = current->next;
	}
	i = 0;
	while(key_value[i])
	{
		tmp = key_value[i];
		j = i + 1;
		while(j < ft_listsize(*head))
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
		printf("declare -x %s\n", key_value[i]);
		i++;
	}
}

void	export_var(char **command, t_env **head, int *j)
{
	int i = 0;
	char    **key_value;
	t_env	*current;
	char	*tmp;

	key_value = (char **)malloc(3);
	if (!ft_isalpha(**(command + (*j))))
	{
		printf("minishell: export: %s:not a valid identifier\n", *(command + (*j)));
		return ;
	}
	while((*(command + (*j)))[i] && (*(command + (*j)))[i]!= '=' && ft_isalnum((*(command + (*j)))[i]))
		i++;
	if ((*(command + (*j)))[i] == '=' || !(*(command + (*j)))[i])
	{
		if (!((*(command + (*j)))[i]))
		{
			key_value[0] = ft_substr(*(command + (*j)), 0, i);
			key_value[1] = ft_strdup("(null)");
		}
		else if ((*(command + (*j)))[i + 1] == '\0')
		{
			key_value[0] = ft_substr(*(command + (*j)), 0, i);
			key_value[1] = ft_strdup("");
		}
		else
		{
			key_value[0] = ft_substr(*(command + (*j)), 0, i);
			key_value[1] = ft_substr(*(command + (*j)), i + 1, ft_strlen(*(command + (*j))) - i);
		}
		current = create_node(key_value);
		ft_lstadd_back(head, current);
	}
	else if (!ft_isalpha((*(command + (*j)))[i]))
	{
		if ((*(command + (*j)))[i] == '+' && (*(command + (*j)))[i + 1] == '=')
		{
			tmp = *(command + (*j));
			*(command + (*j)) = ft_strjoin(ft_substr(*(command + (*j)), 0, i), ft_substr(*(command + (*j)), i + 1, ft_strlen(*(command + (*j))) - i - 1));
			export_var(command, head, j);
			free(tmp);
		}
		else
		{
			printf("minishell: export: %s:not a valid identifier\n", *(command + (*j)));
			return ;
		}
	}
}

void    builtin_export(char **command, t_env **head)
{
	t_env	*current;
	char	*tmp;
	int		i;

	i = 1;
	if (!(*(command + 1)))
		export_env(head);
	else
	{
		while (*(command + i))
		{
			current = *head;
			while(current)
			{
				if (!(ft_strncmp(current->key, *(command + i), ft_strlen(current->key))))
					if ((*(command + i))[ft_strlen(current->key)] == '=' || !((*(command + i))[ft_strlen(current->key)]) || ((*(command + i))[ft_strlen(current->key)] == '+' && (*(command + i))[ft_strlen(current->key) + 1] == '='))
						break;
				current = current->next;
			}
			if (!current)
			{
				export_var(command, head, &i);
			}
			else
			{
				if ((*(command + i))[ft_strlen(current->key)] == '+' && (*(command + i))[ft_strlen(current->key) + 1] == '=')
				{
					tmp = current->value;
					current->value = ft_strjoin(current->value, (*(command + i)) + ft_strlen(current->key) + 2);
					free(tmp);
				}
				else if ((*(command + i))[ft_strlen(current->key)])
				{
					tmp = current->value;
					current->value = ft_substr(*(command + i), ft_strlen(current->key) + 1, ft_strlen(*(command + i)) - ft_strlen(current->key));
					current->print = 1;
					free(tmp);
				}
			}
			i++;
		}
	}
}