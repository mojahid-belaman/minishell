#include "../headers/minishell.h"

char    **split_env(char *line)
{
    char    **key_value;
    key_value = ft_split(line, '=');
    return (key_value);
}

t_env   *create_node(char **key_value)
{
    t_env   *list;
    list = (t_env *)malloc(sizeof(t_env));
    list->key = ft_strdup(key_value[0]);
    list->value = ft_strdup(key_value[1]);
    if (!ft_strncmp(key_value[1], "(null)", 6))
        list->print = 0;
    else
        list->print = 1;
    list->next = NULL;
    return (list);
}

void     get_env(char **envp)
{
    t_var *var = get_struc_var(NULL);
    t_env   *current;
    char    **key_value;

    while (*envp)
    {
        key_value = split_env(*envp);
        current = create_node(key_value);
        ft_lstadd_back(&var->head_env, current);
        envp++;
    }
}