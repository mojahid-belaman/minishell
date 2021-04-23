#include "../headers/minishell.h"

void	check_redir_d(int i, t_var *var)
{
	if (var->redir_right || var->redir_left || var->redir_double)
		hundel_error(token_dr, var);
	else if (var->double_q || var->single_q)
	{
		while (var->line[i] == '>')
		{
			var->line[i] = -var->line[i];
			i++;
		}
	}
	else if (!var->double_q && !var->single_q)
		var->redir_double = 1;
}

void	check_semicolomn(int i, t_var *var)
{
	if (var->redir_right || var->redir_left || var->redir_double
		|| var->semi_colomn || var->pipe)
		hundel_error(token_sc, var);
	else if (var->double_q || var->single_q)
		var->line[i] = -var->line[i];
	else if (!var->double_q && !var->single_q)
		var->semi_colomn = 1;
}

int	count_pip(int i, t_var *var)
{
	int	j;

	j = 0;
	while (var->line[i] && var->line[i] == '|')
	{
		j++;
		i++;
	}
	return (j);
}

void	check_pipe(int i, t_var *var)
{
	if ((var->line[0] == '|' && var->line[i + 1] != '|')
		|| count_pip(i, var) == 3)
		hundel_error(token_pip, var);
	else if ((var->line[0] == '|' && var->line[i + 1] == '|')
		|| count_pip(i, var) > 3)
		hundel_error(token_dpip, var);
	else if (var->pipe && count_pip(i, var) >= 2)
		hundel_error(token_dpip, var);
	else if ((var->redir_right || var->redir_left || var->redir_double
			|| var->semi_colomn) && count_pip(i, var) > 1)
		hundel_error(token_dpip, var);
	else if ((var->redir_right || var->redir_left || var->redir_double
			|| var->semi_colomn) && count_pip(i, var) == 1)
		hundel_error(token_pip, var);
	else if (var->double_q || var->single_q)
		var->line[i] = -var->line[i];
	else if (!var->double_q && !var->single_q)
		var->pipe = 1;
}

void	conv_neg_space(int i, t_var *var)
{
	if (var->double_q || var->single_q)
		var->line[i] = -var->line[i];
}
