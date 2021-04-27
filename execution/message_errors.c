#include "../headers/minishell.h"

void	no_file(t_var *var, char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
	var->status = 1;
}
