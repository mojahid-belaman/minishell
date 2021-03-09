#include "../headers/minishell.h"

char	**split_env(char *line)
{
	char **key_value;

	key_value = ft_split(line, '=');
	return(key_value);
}

t_env	*create_node(char **key_value)
{
	t_env	*list;
	int i;

	i = -1;
	list = (t_env *)malloc(sizeof(t_env));
	list->key = (char *)malloc(sizeof(key_value[0]));
	list->value = (char *)malloc(sizeof(key_value[1]));
	while(key_value[0][++i])
		list->key[i] = key_value[0][i];
	i = -1;
	while(key_value[1][++i])
		list->value[i] = key_value[1][i];
	list->next = NULL;
	return(list);
}

t_env	*get_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	char	**key_value;
	int		i;

	current = (t_env *)malloc(sizeof(t_env));
	head = current;
	while(*envp)
	{
		key_value = split_env(*envp);
		current->next = create_node(key_value);
		envp++;
	}
	return(head);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*head;
	t_env	*env;
	
	env = get_env(envp);
	head = env;
	while(env->next != NULL)
	{
		printf("%s\n", env->key);
		printf("%s\n", env->value);
		env = env->next;
	}
	return()
}