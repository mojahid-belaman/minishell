
int get_index_of_separator(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]))
			break;
		i++;
	}
	return (i);
}

char *get_env_var(char *key)
{
	t_env *current;

	if (g_shell->envs)
	{
		current = g_shell->envs;
		while (current != NULL && ft_strcmp(current->key, key) != 0)
			current = current->next;
		if (current != NULL)
			return (ft_strdup(current->value ? current->value : ft_strdup("")));
	}
	return (ft_strdup(""));
}

if ((*line)[i] == '$' && s == 0)
		{
			char *tmp1;
			char *tmp2;
			int index = 1;
			if ((*line)[i + 1] == '?')
				tmp2 = ft_itoa(g_shell->exit_status);
			else
			{
				index = get_index_of_separator((*line) + i + 1);
				tmp1 = ft_substr((*line) + i + 1, 0, index);
				tmp2 = get_env_var(tmp1);
				tmp2 = tmp2 ? tmp2 : ft_strdup("");
				free(tmp1);
			}
			if (index != 0)
			{
				tmp1 = ft_strjoin(tmp2, (*line) + i + index + 1);
				free(tmp2);
				(*line)[i] = '\0';
				tmp2 = ft_strjoin((*line), tmp1);
				free((*line));
				(*line) = tmp2;
			}
		}