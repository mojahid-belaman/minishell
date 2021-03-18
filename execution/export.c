#include "../headers/minishell.h"

void	export_env(char **command, t_env **head)
{
	char    **key_value;
	char	*tmp;
	char	*anothertmp;
	t_env   *current;
	int i = 0;
	int j = 0;
	key_value = (char **)malloc((ft_lstsize(*head) + 1) * sizeof(char *));
	current = *head;
	while(current)
	{
		key_value[i] = (char *)malloc(ft_strlen(current->key) + ft_strlen(current->value) + 1);
		key_value[i] = ft_strjoin(current->key, "=\"");
		tmp = key_value[i];
		key_value[i] = ft_strjoin(key_value[i], current->value);
		free(tmp);
		tmp = key_value[i];
		key_value[i] = ft_strjoin(key_value[i], "\"");
		free(tmp);
		i++;
		current = current->next;
	}
	i = 0;
	while(key_value[i])
	{
		tmp = key_value[i];
		j = i + 1;
		while(j < ft_lstsize(*head))
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

void	export_var(char **command, t_env **head)
{
	char    **key_value;
	t_env   *current;
	int check_equal = 0;
	int i = 0;

	key_value = (char **)malloc(3);
	if (!ft_isalpha(**(command + 1)))
	{
		printf("minishell: export: %s:not a valid identifier\n", *(command + 1));
		return ;
	}
	while ((*(command + 1))[i])
	{
		if ((*(command + 1))[i] <= 47 || ((*(command + 1))[i] >= 58 && (*(command + 1))[i] <= 64))
		{
			if ((*(command + 1))[i] == 61)
					check_equal = 1;
			else
			{
				printf("minishell: export: %s:not a valid identifier\n", *(command + 1));
				return ;
			}
		}
		i++;
	}
	if (check_equal)
	{
		if ((*(command + 1))[ft_strlen(*(command + 1)) - 1] == '=')
		{
			(*(command + 1))[ft_strlen(*(command + 1)) - 1] = '\0';
			key_value[0] = ft_strdup(*(command + 1));
			key_value[1] = ft_strdup("");
		}
		else
			key_value = ft_split(*(command + 1), '=');
		current = create_node(key_value);
		ft_lstadd_back(head, current);
	}
	else
	{
		printf("need to fix this case here \"export hello\"\n");
	}
}

void    builtin_export(char **command, t_env **head)
{
	t_env	*current;

	current = *head;
	if (!(*(command + 1)))
		export_env(command, head);
	else
		export_var(command, head);	
}