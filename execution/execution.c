
#include "../headers/minishell.h"

int main(void)
{
	char	*buff;

	while (1)
	{
		ft_putstr_fd("minishell ~>  $",1);
		get_next_line(0, &buff);
	}
	return (0);
}
