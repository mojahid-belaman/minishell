#include "../headers/minishell.h"

void	signal_handler_c(int signo)
{
	(void)signo;
	if (g_var->pid == 0)
		exit(0);
	ft_putstr_fd("\n", 2);
	g_var->status = 130;
}

void	signal_handler_quit(int signo)
{
	(void)signo;
	ft_putstr_fd("Quit: 3\n", 2);
	g_var->status = 131;
}
