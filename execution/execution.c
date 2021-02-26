
#include "../headers/minishell.h"

typedef	struct	s_struct
{
	char				*cmd;
	char				*option;
	char				*argument;
	struct	s_struct	*next;
}				t_struct;

t_struct	*init_struct(t_struct *gnrl)
{
	gnrl->cmd = "echo";
	gnrl->option = "-n";
	gnrl->argument = "hello world";
	gnrl->next = NULL;
}

int main(void)
{
	char		*buff;
	t_struct	gnrl;
	int r = 0;

	while (1)
	{
		&gnrl = init_struct(&gnrl);
		/* ft_putstr_fd("minishell ~>  $",fd);*/
		if ((r = ft_strncmp(gnrl->cmd, "echo", 4)) == 0)
		{
			ft_putstr_fd(gnrl->argument, 1);
			if (gnrl->option)
				ft_putchar_fd('\n', 1);
		}
	}
	return (0);
}
