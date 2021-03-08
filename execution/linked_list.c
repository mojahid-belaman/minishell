
#include "../headers/minishell.h"

typedef struct	s_struct {
	char		*var;
	struct		s_struct *next;
}               t_struct;

int main (int argc, char **argv, char **envp)
{
	t_struct	*head;
	int i = -1;
	int j = -1;

	head = (t_struct *)malloc(sizeof(t_struct));
	while(envp[++i])
	{
		head->var = (char *)malloc(sizeof(envp[0]));
		head->next = NULL;
	while (envp[i][++j])
		head->var[i] = envp[0][i];
	}
	printf("%s", head->var);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_struct	*head;
// 	int i = -1;
// 	while(envp[++i])
// 	{
// 		head->next = 
// 	}
// }