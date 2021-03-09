#include "../headers/minishell.h"

typedef	struct	s_env
{
	char	*key;
	char	*value;
	struct	s_env *next;
}				t_env;

char	**split_env(char *line)
{
	char **key_value;

	key_value = ft_split(line, '=');
	return(key_value);
}

t_env	*create_node(t_env *node, char **key_value)
{
	t_env	*list;
	int i;

	i = -1;
	list = (t_env *)malloc(sizeof(t_env));
	list->key = ft_strdup(key_value[0]);
	list->value = ft_strdup(key_value[1]);
	list->next = NULL;
	return(list);
}

void	ft_lstadd_back_m(t_env **alst, t_env *new)
{
	t_env *lst;

	lst = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

t_env	*get_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	char	**key_value;

	head = NULL;
	while(*envp)
	{
		key_value = split_env(*envp);
		current = create_node(current, key_value);
		ft_lstadd_back_m(&head, current);
		envp++;
	}
	return(head);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*head;
	t_env	*env;

	env = get_env(envp);
	while(env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}