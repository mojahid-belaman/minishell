
#include "../headers/minishell.h"

void    print_list_env(t_env *head)
{
    t_env *curr;

    curr = head;
	if (!curr)
		puts("failed");
    while (curr)
    {
        printf("|%s||%s|\n", curr->key, curr->value);
        curr = curr->next;
    }
    
}
void	execute()
{
    // need to fix the export error!! it segfaults.
	builtin();
}
