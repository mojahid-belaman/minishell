
#include "../headers/minishell.h"

int main()
{
	int r = 1;
	char *buff;

	while (r > 0)
	{
		ft_putstr_fd("minishell ~>  $",1);
		// while()
		r = read(0, buff, 10);
		printf("%s", buff);
	}
}
